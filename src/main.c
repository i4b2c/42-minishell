#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

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
