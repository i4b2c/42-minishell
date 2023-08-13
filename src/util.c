#include "../include/minishell.h"

char *ft_mllstrcpy(char *str)
{
	int i;
	int len;
	char *temp;

	i = 0;
	len = ft_strlen(str);
	temp = malloc(sizeof(char) * (len + 1));
	while(str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return temp;
}
