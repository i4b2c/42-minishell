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
//testes


void add_list(t_data *data,t_varlst *temp_var)
{
	if(data->var_head == NULL)
		data->var_head = temp_var;
	else
	{
		while(data->var_head->next != NULL)
			data->var_head = data->var_head->next;
		data->var_head->next = temp_var;
	}
}

int get_index_fenv(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	return i;
}

int get_index_eenv(char *str)
{
	int i;
	int j;

	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	j = 0;
	while(str[i+j])
		j++;
	return j;
}

void add_env(t_data *data,char *var)
{
	t_varlst *temp_var;
	char **envp;
	int i;
	int j;

	i = get_index_env(var) + 1;
	temp_var = malloc(sizeof(t_varlst));
	if(!temp_var)
		error(MALLOC,NULL);
	envp = ft_split(var,' ');
	j = 0;
	while(envp[++j])
	{
		temp_var->var_name = malloc(get_index_fenv(envp[j]) * sizeof(char));
		temp_var->var_value = malloc(get_index_eenv(envp[j]) + 1 * sizeof(char));
		temp_var->next = NULL;
		ft_strlcpy(temp_var->var_name,envp[j],get_index_fenv(envp[j])+1);
		ft_strcpy(temp_var->var_value,envp[j]+get_index_fenv(envp[j])+1);
		add_list(data,temp_var);
	}
}

bool check_input_env(char *var)
{
	if(!ft_isalpha(var[0]))
		return false;
	return true;
}
