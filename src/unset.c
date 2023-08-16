#include "../include/minishell.h"

void exec_unset(t_data *data, char **input)
{
	t_varlst *temp_var;
	t_varlst *temp_teste;
	int i;

	i = 0;
	while(input[++i])
	{
		//check input depois !! importante
		temp_var = data->var_head;
		while(temp_var)
		{
			if(temp_var->next && !strncmp(temp_var->next->var_name,input[i],ft_strlen(input[i])))
			{
				temp_teste = temp_var->next->next;
				free(temp_var->next->var_name);
				free(temp_var->next->var_value);
				free(temp_var->next);
				temp_var->next = temp_teste;
				break;
			}
			temp_var = temp_var->next;
		}
	}
	free_strings(input);
}
