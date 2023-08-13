#include "../include/minishell.h"

int len_strings(char **cmd)
{
	int i;

	i = 0;
	while(cmd[i])
		i++;
	return i;
}

void print_string(char **str)
{
	int i;

	i = 0;
	while(str[i])
		ft_printf("%s\n",str[i++]);
}
