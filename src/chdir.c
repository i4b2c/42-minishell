#include "../include/minishell.h"

void exec_chdir(char *input)
{
	char **cmd;

	cmd = ft_split(input,' ');
	if(len_strings(cmd) > 2)
		write(2,"minishell: too many arguments\n",30);
	else if(chdir(cmd[1]) != 0)
		perror("minishell ");
	free_strings(cmd);
	return ;
}
