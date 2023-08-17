#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;
	int temp_stdout;
	int temp_stdin;

	if(ac > 1 && av)
		error(ARGS,NULL);
	data = get_data(ac,av,envp);
	init_signal();
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while(1)
	{
		//reset();
		dup2(temp_stdout,STDOUT_FILENO);
		dup2(temp_stdin,STDIN_FILENO);
		input = get_input();
		if(!input[0])
			free(input);
		else
		{
			add_history(input);
			data->tokens_head = tokens_input(input);
			data->check_in = false;
			if(!strncmp(data->tokens_head->command,"exit",4))
			{
				free_data(&data);
				break;
			}
			exec_tokens(data);
			unlink(TEMP_FILE);
			free_tokens(data);
		}
	}
	return 0;
}
