/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:28:11 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:28:11 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern volatile long long g_exit_status;

char	*check_command(char *command, char **path)
{
	char	*teste;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		teste = malloc(256);
		ft_strcpy(teste, path[i]);
		ft_strlcat(teste, "/", 256);
		ft_strlcat(teste, command, 256);
		if (access(teste, X_OK) == 0)
			return (teste);
		i++;
		free(teste);
	}
	return (NULL);
}

char	*ft_getenv(const char *str, t_data *data)
{
	t_varlst	*temp_var;

	temp_var = data->var_head;
	while (temp_var)
	{
		if (!strncmp(temp_var->var_name, str, ft_strlen((char *)temp_var->var_name)))
			return (ft_mllstrcpy(temp_var->var_value));
		temp_var = temp_var->next;
	}
	return (ft_calloc(1, 1));
}

void	ft_execve(char **command, t_data *data)
{
	char	*path;
	char	*check;
	char	**check_split;

	path = ft_getenv("PATH", data);
	if (!path)
	{
		write(2, "minishell : command not found\n", 30);
		free_strings(command);
		exit(0);
	}
	check_split = ft_split(path, ':');
	check = check_command(command[0], check_split);
	if (check)
		execve(check, command, NULL);
	if (!access(command[0], X_OK))
		execve(command[0], command, NULL);
	dup2(STDOUT_FILENO, 1);
	if(command[0][0] == '.' && command[0][1] == '/')
	{
		g_exit_status = 126;
		perror("minishell");
	}
	else
	{
		g_exit_status = 127;
		write(2, "minishell : command not found\n", 30);
	}
	free_strings(command);
	exit(g_exit_status);
}

void	read_stdin(char *str, int fd_temp)
{
	char	*input;
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

int	pipe_string(t_tokens *tokens)
{
	t_tokens	*temp;
	int			pipe;

	temp = tokens;
	pipe = 0;
	while (temp)
	{
		if (temp->type == PIPE)
			pipe++;
		temp = temp->next;
	}
	return (pipe);
}

void	choose_exec(char **command, t_data *data)
{
	pid_t	pid;

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
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, child_process);
			ft_execve(command, data);
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
			g_exit_status = WEXITSTATUS(status);
		}
	}
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*cut_quotes(char *input, char quote)
{
	char	*temp;
	int		i;
	int		i_temp;

	i = 0;
	i_temp = 0;
	temp = malloc(sizeof(char) * ft_strlen(input));
	while (input[i])
	{
		if (input[i] != quote)
		{
			temp[i_temp] = input[i];
			i_temp++;
		}
		i++;
	}
	temp[i_temp] = 0;
	return (temp);
}

void	exec_tokens(t_data *data)
{
	char		**command;
	int			len;
	t_tokens	*temp;
	int			i;
	pid_t		pid;
	int			fd;
	bool		check_pipe;
	int temp_i;
	int temp_o;

	temp_i = dup(STDIN_FILENO);
	temp_o = dup(STDOUT_FILENO);
	i = 0;
	temp = data->tokens_head;
	len = 0;
	check_pipe = false;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	command = malloc(sizeof(char *) * (len + 1));
	temp = data->tokens_head;
	while (temp)
	{
		if (temp->type == NORMAL)
		{
			command[i] = ft_mllstrcpy(temp->command);
			i++;
		}
		else if (temp->type == RDR_OUT
			|| temp->type == RDR_AP_OUT)
			{
				data->check_out = true;
				// if(!change_stdout(temp->command, temp->type))
				// 	return ;
				temp->fd_out = change_stdout(temp->command, temp->type);
			}
		else if (temp->type == RDR_IN)
		{
			data->check_in = true;
			if(!change_stdin(temp->command))
				return ;
		}
		else if (temp->type == RDR_RD_IN)
		{
			data->check_in = true;
			read_stdin(temp->command, temp_i);
		}
		else if (temp->type == PIPE)
		{
			check_pipe = true;
			if (!data->check_out)
				change_stdout(TEMP_FILE_OUT, RDR_OUT);
			command[i] = NULL;
			choose_exec(command, data);
			dup2(temp_i, STDIN_FILENO);
			if (!data->check_out)
			{
				dup2(temp_o, STDOUT_FILENO);
				fd = open(TEMP_FILE_OUT, O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			data->check_in = false;
			data->check_out = false;
			free_strings(command);
			command = malloc(sizeof(char *) * (len + 1));
			i = 0;
		}
		temp = temp->next;
	}
	command[i] = NULL;
	if (!data->check_out)
		dup2(temp_o, STDOUT_FILENO);
	if (!data->check_in && check_pipe)
	{
		dup2(temp_i, STDIN_FILENO);
		int fd_teste = open(TEMP_FILE_OUT, O_RDONLY);
		if (fd_teste == -1)
			fd_teste = open(TEMP_FILE_OUT, O_CREAT | O_RDONLY);
		dup2(fd_teste, STDIN_FILENO);
	}
	choose_exec(command, data);
	unlink(TEMP_FILE_OUT);
	unlink(TEMP_FILE);
}
