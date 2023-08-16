#include "../include/minishell.h"

void exec_chdir(char **input)
{
	if(len_strings(input) > 2)
		write(2,"minishell: too many arguments\n",30);
	else if(chdir(input[1]) != 0)
		perror("minishell ");
	free_strings(input);
	return ;
}
