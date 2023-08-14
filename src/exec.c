#include "../include/minishell.h"

void	ft_strcpy_path(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 5;
	j = 0;
	while (s2[i] != 0)
	{
		s1[j] = s2[i];
		i++;
		j++;
	}
}

char	**getpath(char **str)
{
	int		i;
	char	*path_simple;
	char	**path;

	i = 0;
	while (str[i] != NULL)
	{
		if (!(ft_strncmp("PATH=", str[i], 5)))
		{
			path_simple = malloc(ft_strlen(str[i]));
			ft_strcpy_path(path_simple, str[i]);
		}
		i++;
	}
	path = NULL;
	path = ft_split(path_simple, ':');
	free(path_simple);
	return (path);
}

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

void	exec(char *command,t_data *data)
{
	char	*path;
	char	*check;
	char	**cmd;

	cmd = ft_split(command, ' ');
	path = ft_getenv("PATH",data);
	if(path == NULL)
	{
		write(2,"minishell : command not found\n",30);
		free_strings(cmd);
		exit(0);
	}
	check = check_command(cmd[0], ft_split(path,':'));
	if (check != NULL)
		execve(check, cmd, NULL);
	if(access(cmd[0],X_OK) == 0)
		execve(cmd[0],cmd, NULL);
	dup2(STDOUT_FILENO,1);
	write(2,"minishell : command not found\n",30);
	free(command);
	exit(0);
}

void check_exec(t_data *data, char *input)
{
	pid_t pid;

	add_history(input);
	if(!strncmp(input,"export",6))
	{
		if(ft_strlen(input) > 6)
			change_env(data,input);
		else
			print_export(data);
	}
	else if(!strncmp(input,"env",3))
		print_env(data);
	else if(!strncmp(input,"cd",2))
		exec_chdir(input);
	else if(!strncmp(input,"echo",4))
		exec_echo(data,input);
	else if(!strncmp(input,"unset",5))
		exec_unset(data,input);
	else if(input[0] == 0)
		free(input);
	else
	{
		pid = fork();
		if(pid == (pid_t)0)
		{
			signal(SIGINT,child_process);
			exec(input,data);
			free(input);
			exit(0);
		}
		else
			waitpid(pid,NULL,0);
		free(input);
	}
}
