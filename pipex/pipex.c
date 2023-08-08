/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:32:41 by icaldas           #+#    #+#             */
/*   Updated: 2023/07/26 13:34:01 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *command, char **envp)
{
	char	**path;
	char	*check;
	char	**cmd;

	cmd = ft_split(command, ' ');
	path = getpath(envp);
	check = check_command(cmd[0], path);
	if (check != NULL)
		execve(check, cmd, envp);
	return ;
}

void	child_process(char **av, char **envp, int fd[2])
{
	int	file;

	file = open(av[1], O_RDONLY);
	if (file < 0)
		error();
	dup2(fd[1], STDOUT_FILENO);
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	exec(av[2], envp);
	return ;
}

void	parent_process(char **av, char **envp, int fd[2])
{
	int	file;

	file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file < 0)
		error();
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	exec(av[3], envp);
	return ;
}

void	pipex(char **av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		child_process(av, envp, fd);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(av, envp, fd);
	}
	return ;
}

