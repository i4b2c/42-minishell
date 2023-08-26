#include "../include/minishell.h"

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

char *ft_getenv(const char *str,t_data *data)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var)
	{
		if(!strncmp(temp_var->var_name,str,4))
			return (ft_mllstrcpy(temp_var->var_value));
		temp_var = temp_var->next;
	}
	return NULL;
}

void ft_execve(char **command,t_data *data)
{
	char *path;
	char *check;

	path = ft_getenv("PATH",data);
	if(!path)
	{
		write(2,"minishell : command not found\n",30);
		free_strings(command);
		exit(0);
	}
	int i = 0;
	check = check_command(command[0],ft_split(path,':'));
	if(check)
		execve(check,command,NULL);
	if(!access(command[0],X_OK))
		execve(command[0],command,NULL);
	dup2(STDOUT_FILENO,1);
	write(2,"minishell : command not found\n",30);
	free(command);
	exit(0);
}


void read_stdin(char *str,int fd_temp)
{
	char *input;
	int fd;
	int check_unlink;

	//check_unlink = unlink(TEMP_FILE);
	fd = open(TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC , 0666);
	dup2(fd_temp,STDIN_FILENO);
	if(fd == -1)
		exit(0);
	while(1)
	{
		input = readline("> ");
		if(!ft_strncmp(input,str,ft_strlen(str)))
			break;
		else
		{
			write(fd,input,ft_strlen(input));
			write(fd,"\n",1);
		}
		free(input);
	}
	close(fd);
	fd = open(TEMP_FILE , O_RDONLY);
	dup2(fd,STDIN_FILENO);
	//lembrar de dar unlink no arq_temp.txt
}

int pipe_string(t_tokens *tokens)
{
	t_tokens *temp;
	int pipe;

	temp = tokens;
	pipe = 0;
	while(temp)
	{
		if(temp->type == PIPE)
			pipe++;
		temp = temp->next;
	}
	return pipe;
}

bool try_simple_exec(char **command,t_data *data)
{
	if(!ft_strncmp(command[0],"export",6))
	{
		if(data->tokens_head->next != NULL
			&& data->tokens_head->next->type == NORMAL)
			change_env(data,command);
		else
			print_export(data);
		return true;
	}
	else if(!ft_strncmp(command[0],"unset",5))
	{
		exec_unset(data,command);
		return true;
	}
	else if(!ft_strncmp(command[0],"cd",2))
	{
		exec_chdir(command);
		return true;
	}
	else if(!strncmp(command[0],"env",3))
	{
		print_env(data);
		return true;
	}
	else if(!strncmp(command[0],"echo",4))
	{
		exec_echo(data,command);
		return true;
	}
	return false;
}

void exec_tokens(t_data *data)
{
	char **command;
	int len;
	t_tokens *temp;
	int i;
	pid_t pid;
	int fd;

	int temp_i = dup(STDIN_FILENO);
	int temp_o = dup(STDOUT_FILENO);

	i = 0;
	temp = data->tokens_head;
	len = 0;
	while(temp)
	{
		temp = temp->next;
		len++;
	}
	command = malloc(sizeof(char *) * (len + 1));
	temp = data->tokens_head;
	while(temp)
	{
		if(temp->type == NORMAL)
		{
			command[i] = ft_mllstrcpy(temp->command);
			i++;
		}
		else if(temp->type == RDR_OUT
			|| temp->type == RDR_AP_OUT)
			{
				data->check_out = true;
				temp->fd_out = change_stdout(temp->command,temp->type);
			}
		else if(temp->type == RDR_IN)
		{
			data->check_in = true;
			change_stdin(temp->command);
		}
		else if(temp->type == RDR_RD_IN)
		{
			data->check_in = true;
			read_stdin(temp->command,temp_i);
		}
		else if(temp->type == PIPE)
		{
			fd = open(TEMP_FILE_OUT, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if(!data->check_out)
				dup2(fd,STDOUT_FILENO);

			command[i] = NULL;
			if(!ft_strncmp(command[0],"export",6))
			{
				if(data->tokens_head->next != NULL
					&& data->tokens_head->next->type == NORMAL)
					change_env(data,command);
				else
					print_export(data);
			}
			else if(!ft_strncmp(command[0],"unset",5))
				exec_unset(data,command);
			else if(!ft_strncmp(command[0],"cd",2))
				exec_chdir(command);
			else if(!strncmp(command[0],"env",3))
				print_env(data);
			else if(!strncmp(command[0],"echo",4))
				exec_echo(data,command);
			else
			{
				pid = fork();
				if(pid == 0)
				{
					signal(SIGINT,child_process);
					ft_execve(command,data);
				}
				else
					waitpid(pid,NULL,0);
			}
			if(!data->check_out)
			{
				close(fd);
				dup2(temp_o,STDOUT_FILENO);
				fd = open(TEMP_FILE_OUT,O_RDONLY);
				dup2(fd,STDIN_FILENO);
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
	if(!data->check_out)
		dup2(temp_o,STDOUT_FILENO);
	if(!data->check_in)
		change_stdin(TEMP_FILE);
	if(!ft_strncmp(command[0],"export",6))
	{
		if(data->tokens_head->next != NULL
			&& data->tokens_head->next->type == NORMAL)
			change_env(data,command);
		else
			print_export(data);
	}
	else if(!ft_strncmp(command[0],"unset",5))
		exec_unset(data,command);
	else if(!ft_strncmp(command[0],"cd",2))
		exec_chdir(command);
	else if(!strncmp(command[0],"env",3))
		print_env(data);
	else if(!strncmp(command[0],"echo",4))
		exec_echo(data,command);
	else
	{
		pid = fork();
		if(pid == 0)
		{
			signal(SIGINT,child_process);
			ft_execve(command,data);
		}
		else
			waitpid(pid,NULL,0);
	}
	unlink(TEMP_FILE_OUT);
	unlink(TEMP_FILE);
}
