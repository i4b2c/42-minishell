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
	t_varlst *atual;

	atual = NULL;
	if(data->var_head == NULL)
		data->var_head = temp_var;
	else
	{
		atual = data->var_head;
		while(atual->next != NULL)
			atual = atual->next;
		atual->next = temp_var;
	}
}

int strtok_env(char *str)
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

void add_env(t_data *data,char *var)
{
	t_varlst *temp_var;
	char **envp;
	char **command;
	int j;

	envp = ft_split(var,' ');
	j = 0;
	while(envp[++j])
	{
		temp_var = malloc(sizeof(t_varlst));
		if(!temp_var)
			error(MALLOC,NULL);
		command = ft_split(envp[j],'=');
		if(!command[1])
			return ;
		else
		{
				temp_var->var_name = ft_mllstrcpy(command[0]);
				temp_var->var_value = ft_mllstrcpy(command[1]);
				temp_var->next = NULL;
				add_list(data,temp_var);
				temp_var = temp_var->next;
		}
	}
}

bool check_input_env(char *var)
{
	if(!ft_isalpha(var[0]))
		return false;
	return true;
}
