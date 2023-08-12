#include "../include/minishell.h"

void print_env(t_data *data)
{
	char **temp;
	t_varlst *temp_var;
	int i;

	i = 0;
	temp = data->envp;
	while(temp[i])
		ft_printf("%s\n",temp[i++]);
	temp_var = data->var_head;
	while(temp_var != NULL)
	{
		ft_printf("%s=%s\n",temp_var->var_name,temp_var->var_value);
		temp_var = temp_var->next;
	}

}

int get_index_env(char *str)
{
	int i;

	i = 0;
	while(str[i] != '=' && str[i] != 0)
		i++;
	return (i);
}

void add_env(t_data *data,char *var)
{
	t_varlst *temp_var;
	int i;

	i = get_index_env(var) + 1;
	temp_var = malloc(sizeof(t_varlst));
	if(!temp_var)
		error(MALLOC,NULL);
	temp_var->var_name = malloc(15 * sizeof(char));
	temp_var->var_value = malloc(15 * sizeof(char));
	temp_var->next = NULL;
	ft_strlcpy(temp_var->var_name,var,i);
	ft_strcpy(temp_var->var_value,var+i);
	if(data->var_head == NULL)
		data->var_head = temp_var;
	else
	{
		while(data->var_head->next != NULL)
			data->var_head = data->var_head->next;
		data->var_head->next = temp_var;
	}
}

bool check_input_env(char *var)
{
	if(!ft_isalpha(var[0]))
		return false;
	return true;
}
