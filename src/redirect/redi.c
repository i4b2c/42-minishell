/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:15:29 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 16:15:29 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

int	change_stdout(char *str, t_type type)
{
	int	fd;

	if (type == RDR_OUT)
	{
		unlink(str);
		fd = open(str, O_WRONLY | O_CREAT, 0666);
	}
	else if (type == RDR_AP_OUT)
		fd = open(str, O_WRONLY | O_CREAT, 0666 | O_APPEND);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

bool	change_stdin(char *str)
{
	int	fd;
	int	check_access;

	check_access = access(str, R_OK);
	if (check_access == -1)
	{
		perror("minishell");
		g_exit_status = 1;
		return (false);
	}
	fd = open(str, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	return (true);
}

void	execute_rdin(int fd, char *str)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!ft_strncmp(input, str, ft_strlen(str)))
			break ;
		else
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
		}
		free(input);
	}
}

void	read_stdin(char *str, int fd_temp)
{
	int		fd;
	int		check_unlink;
	pid_t	pid;

	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd_temp, STDIN_FILENO);
	if (fd == -1)
		exit(0);
	pid = fork();
	if (pid == (pid_t)0)
	{
		signal(SIGINT, child_process);
		execute_rdin(fd, str);
		exit(0);
	}
	else
	{
		close(fd);
		fd = open(TEMP_FILE, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
