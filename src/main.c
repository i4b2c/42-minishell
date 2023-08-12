#include "../include/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;
	pid_t pid;

	if(ac > 1 && av)
		error(ARGS,NULL);
	data = get_data(ac,av,envp);
	while(1)
	{
		input = get_input();
		input = ft_strtrim(input," \t");
		if(!strcmp(input,"exit"))
		{
			free(input);
			free_data(&data);
			break;
		}
		else
		{
			pid = fork();
			if(pid == (pid_t)0)
				exec(input);
			else
				waitpid(pid,NULL,0);
			free(input);
		}
	}
	// if(check_input_env("ok=2"))
	// 	add_env(data,"ok=2");
	// print_env(data);
	//print_env(data);
	//add_env(&data?)
	// free_data(&data);
	return 0;
}
