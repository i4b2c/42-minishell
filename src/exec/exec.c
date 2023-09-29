/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:28:11 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/13 14:23:09 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

void	ft_execve(char **command, t_data *data)
{
	char		*path;
	char		*check;
	char		**check_split;
	struct stat	file_stat;

	path = ft_getenv("PATH", data, false);
	if (!path)
		exit(error_nf(command));
	check_split = ft_split(path, ':');
	check = check_command(command[0], check_split);
	if (check)
		execve(check, command, data->envp);
	if (!access(command[0], X_OK))
		execve(command[0], command, data->envp);
	dup2(STDOUT_FILENO, 1);
	if (access(command[0], F_OK) == -1)
		exit(error_nf(command));
	if (access(command[0], X_OK) == -1)
		exit(g_exit_status);
	else if (lstat(command[0], &file_stat) == 0 && ft_strchr(command[0], '/')
		&& (S_ISDIR(file_stat.st_mode)))
		exit(error_dir(command));
	else
		exit(error_nf(command));
}

void	exec_command(char **command, t_data *data)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, child_process);
		ft_execve(command, data);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status != 2)
			g_exit_status = WEXITSTATUS(status);
	}
}

void	choose_exec(char **command, t_data *data)
{
	if (!ft_strncmp(command[0], "export", 6))
	{
		if (data->tokens_head->next != NULL
			&& data->tokens_head->next->type == NORMAL)
			change_env(data, command);
		else
			print_export(data);
	}
	else if (!ft_strncmp(command[0], "unset", 5))
		exec_unset(data, command);
	else if (!ft_strncmp(command[0], "cd", 2))
		exec_chdir(command);
	else if (!strncmp(command[0], "env", 3))
		print_env(data);
	else
		exec_command(command, data);
}

char	**exec_pipe(t_data *data, char **command, int len, int i)
{
	int	fd;

	if (!data->check_out)
		change_stdout(TEMP_FILE_OUT, RDR_OUT);
	command[i] = NULL;
	choose_exec(command, data);
	dup2(data->fd_in, STDIN_FILENO);
	if (!data->check_out)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		fd = open(TEMP_FILE_OUT, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	data->check_in = false;
	data->check_out = false;
	return (command);
}

void	exec_tokens(t_data *data)
{
	char		**command;
	int			len;
	t_tokens	*temp;
	int			i;

	i = 0;
	len = len_tokens(data->tokens_head);
	command = init_command(len);
	temp = data->tokens_head;
	while (temp)
	{
		if (!choose_redirect(&i, command, temp, data))
			return ;
		temp = temp->next;
	}
	command[i] = NULL;
	if (!data->check_out)
		dup2(data->fd_out, STDOUT_FILENO);
	if (!data->check_in && data->check_pipe)
		last_fd(data);
	choose_exec(command, data);
	free_strings(command);
	free(command);
	unlink(TEMP_FILE_OUT);
	unlink(TEMP_FILE);
}
