#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;
	int temp_stdout;

	if(ac > 1 && av)
		error(ARGS,NULL);
	data = get_data(ac,av,envp);
	init_signal();
	temp_stdout = dup(STDOUT_FILENO);
	//temp_int = STDOUT_FILENO;
	while(1)
	{
		dup2(temp_stdout,STDOUT_FILENO);
		input = get_input();
		if(!strcmp(input,"exit"))
		{
			free(input);
			free_data(&data);
			break;
		}
		else if(ft_strchr(input,'>'))
			input = change_stdout(input);
		check_exec(data,input);
		//free(input);
		//dup2(temp_int,STDOUT_FILENO);
	}
	return 0;
}
