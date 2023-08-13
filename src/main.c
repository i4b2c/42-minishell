#include "../include/minishell.h"

volatile long long	g_exit_status = 0;



bool check_exist_env(t_data *data, char *input)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var)
	{
		if(!ft_strncmp(temp_var->var_name,input,ft_strlen(input)))
			return true;
		temp_var = temp_var->next;
	}
	return false;
}

void change_exist_env(t_data *data, char **command)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var)
	{
		if(!ft_strncmp(temp_var->var_name,command[0],ft_strlen(command[0])))
		{
			if(temp_var->var_value)
				free(temp_var->var_value);
			temp_var->var_value = malloc(sizeof(char) * (ft_strlen(command[1]) + 1));
			ft_strcpy(temp_var->var_value,command[1]);
			return ;
		}
		temp_var = temp_var->next;
	}
	return ;
}

void change_env(t_data *data, char *input)
{
	t_varlst *temp_var;
	char **envp;
	char **command;
	int j;

	envp = ft_split(input,' ');
	j = 0;
	while(envp[++j])
	{
		temp_var = malloc(sizeof(t_varlst));
		if(!temp_var)
			error(MALLOC,NULL);
		command = ft_split(envp[j],'=');
		if(check_exist_env(data,command[0]))
			change_exist_env(data,command);
		else
		{
				temp_var->var_name = ft_mllstrcpy(command[0]);
				temp_var->var_value = ft_mllstrcpy(command[1]);
				temp_var->next = NULL;
				add_list(data,temp_var);
				temp_var = temp_var->next;
		}
		free_strings(command);
	}
	free_strings(envp);
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
					//add_env(data,input);
				else
					print_export(data);
			}
			else if(!strncmp(input,"env",3))
					print_env(data);
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
