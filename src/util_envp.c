#include "../include/minishell.h"

void print_env(t_data *data)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var != NULL)
	{
		ft_printf("%s=%s\n",temp_var->var_name,temp_var->var_value);
		temp_var = temp_var->next;
	}

}
