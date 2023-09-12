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

extern volatile long long	g_exit_status;

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
		if (!strncmp(temp_var->var_name, str,
				ft_strlen((char *)temp_var->var_name)))
			return (ft_mllstrcpy(temp_var->var_value));
		temp_var = temp_var->next;
	}
	return (ft_calloc(1, 1));
}

int	error_dir(char **command)
{
	g_exit_status = 126;
	write(2, "minishell : Is a directory\n", 28);
	free_strings(command);
	return (g_exit_status);
}

int	error_nf(char **command)
{
	write(2, "minishell : command not found\n", 30);
	g_exit_status = 127;
	free_strings(command);
	return (g_exit_status);
}

int	error_access(char **command)
{
	perror("minishell");
	g_exit_status = 126;
	free_strings(command);
	return (g_exit_status);
}

void	ft_execve(char **command, t_data *data)
{
	char		*path;
	char		*check;
	char		**check_split;
	struct stat	file_stat;

	path = ft_getenv("PATH", data);
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

void	exec_command(char **command, t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, child_process);
		ft_execve(command, data);
	}
	else
	{
		waitpid(pid, &status, 0);
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
	free_strings(command);
	command = malloc(sizeof(char *) * (len + 1));
	return (command);
}

int	len_tokens(t_tokens *head)
{
	int	res;

	res = 0;
	while (head)
	{
		res++;
		head = head->next;
	}
	return (res);
}

bool	choose_redirect(int *i,
	char **command, t_tokens *temp, t_data *data)
{
	if (temp->type == NORMAL)
		command[(*i)++] = ft_mllstrcpy(temp->command);
	else if (temp->type == RDR_OUT || temp->type == RDR_AP_OUT)
	{
		data->check_out = true;
		temp->fd_out = change_stdout(temp->command, temp->type);
	}
	else if (temp->type == RDR_IN)
	{
		data->check_in = true;
		if (!change_stdin(temp->command))
			return (false);
	}
	else if (temp->type == RDR_RD_IN)
	{
		data->check_in = true;
		read_stdin(temp->command, data->fd_in);
	}
	else if (temp->type == PIPE)
	{
		data->check_pipe = true;
		command = exec_pipe(data, command, len_tokens(data->tokens_head), i);
		(*i) = 0;
	}
	return (true);
}

void	last_fd(t_data *data)
{
	int	fd_temp;

	dup2(data->fd_in, STDIN_FILENO);
	fd_temp = open(TEMP_FILE_OUT, O_RDONLY);
	if (fd_temp == -1)
		fd_temp = open(TEMP_FILE_OUT, O_CREAT | O_RDONLY);
	dup2(fd_temp, STDIN_FILENO);
}

void	exec_tokens(t_data *data)
{
	char		**command;
	int			len;
	t_tokens	*temp;
	int			i;

	i = 0;
	len = len_tokens(data->tokens_head);
	command = malloc(sizeof(char *) * (len + 1));
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
	unlink(TEMP_FILE_OUT);
	unlink(TEMP_FILE);
}
