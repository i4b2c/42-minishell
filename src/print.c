#include "../include/minishell.h"

void print_string(char **str)
{
	int i;

	i = 0;
	while(str[i])
		ft_printf("%s\n",str[i++]);
}
