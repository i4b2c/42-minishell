#include "../include/minishell.h"

void error(char *str,char *str_extra)
{
	write(2,str,ft_strlen(str));
	if(str_extra)
	{
		write(2,str_extra,ft_strlen(str_extra));
		write(2,"\n",1);
	}
	//exit(EXIT_FAILURE);
	return ;
}
