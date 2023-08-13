#include "../include/minishell.h"

void exec_unset(t_data *data, char *input)
{
	char **command;
	t_varlst *temp_var;
	t_varlst *temp_teste;
	int i;

	command = ft_split(input,' ');
	i = 0;
	while(command[++i])
	{
		//check input depois !! importante
		temp_var = data->var_head;
		while(temp_var)
		{
			if(temp_var->next && !strncmp(temp_var->next->var_name,command[i],ft_strlen(command[i])))
			{
				temp_teste = temp_var->next->next;
				free(temp_var->next->var_name);
				free(temp_var->next->var_value);
				free(temp_var->next);
				temp_var->next = temp_teste;
				return ;
			}
			temp_var = temp_var->next;
		}
	}
}
