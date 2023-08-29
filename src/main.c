#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

int get_len_pipes(char *input)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while(input[i])
	{
		if(input[i] == '|')
			len++;
		i++;
	}
	return (len);
}

char *new_input(char *input)
{
	int i_input;
	int i_new;
	char *new_input;

	i_input = 0;
	i_new = 0;
	new_input = malloc(((get_len_pipes(input) * 2) + 1 + ft_strlen(input)) * sizeof(char));
	while(input[i_input])
	{
		if(input[i_input] == '|')
		{
			new_input[i_new] = ' ';
			new_input[i_new+1] = input[i_input];
			new_input[i_new+2] = ' ';
			i_new += 2;
		}
		else
			new_input[i_new] = input[i_input];
		i_new++;
		i_input++;
	}
	new_input[i_new] = 0;
	free(input);
	return new_input;
}

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
			input = new_input(input);
			data->tokens_head = tokens_input(input,data);
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
