#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

void search_envp(t_data *data, char *cmd)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var)
	{
		if(!strncmp(temp_var->var_name,cmd+1,ft_strlen(cmd)-1))
		{
			ft_printf("%s",temp_var->var_value);
			return ;
		}
		temp_var = temp_var->next;
	}
}

void exec_echo(t_data *data, char *input)
{
	char **command;
	char *temp;
	int i;

	command = ft_split(input,' ');
	i = 0;
	while(command[++i])
	{
		temp = ft_strtrim(command[i],"\"");
		if(temp[0] == '$')
			search_envp(data,temp);
		else
			ft_printf("%s",temp);
		if(command[i+1])
			write(STDOUT_FILENO," ",1);
		free(temp);
	}
	write(STDOUT_FILENO,"\n",1);
	free_strings(command);
}

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;
	pid_t pid;

	if(ac > 1 && av)
		error(ARGS,NULL);
	data = get_data(ac,av,envp);
	init_signal();
	while(1)
	{
		input = get_input();
		if(input)
		{
			if(!strcmp(input,"exit"))
			{
				free(input);
				free_data(&data);
				break;
			}
			else if(!strncmp(input,"export",6))
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
			else if(input[0] == 0)
				free(input);
			else
			{
				pid = fork();
				if(pid == (pid_t)0)
				{
					signal(SIGINT,child_process);
					exec(input);
					exit(0);
				}
				else
					waitpid(pid,NULL,0);
				free(input);
			}
		}
	}
	return 0;
}
