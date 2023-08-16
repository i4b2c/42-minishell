#include "../include/minishell.h"

//colocar na utils
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

bool check_exist_env(t_data *data, char *input)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var)
	{
		if(!ft_strncmp(temp_var->var_name,input,ft_strlen(input)))
			return true;
		temp_var = temp_var->next;
	}
	return false;
}

void change_exist_env(t_data *data, char **command)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var)
	{
		if(!ft_strncmp(temp_var->var_name,command[0],ft_strlen(command[0])))
		{
			if(temp_var->var_value)
				free(temp_var->var_value);
			temp_var->var_value = malloc(sizeof(char) * (ft_strlen(command[1]) + 1));
			ft_strcpy(temp_var->var_value,command[1]);
			return ;
		}
		temp_var = temp_var->next;
	}
	return ;
}

bool check_input_env(char *str)
{
	if(ft_isalpha(str[0]))
		return false;
	return true;
}

void change_env(t_data *data, char **input)
{
	t_varlst *temp_var;
	char **command;
	int j;

	j = 0;
	while(input[++j])
	{
		//melhorar o checker
		if(check_input_env(input[j]))
			ft_printf("minishell: `%s': not a valid identifier\n",input[j]);
		else
		{
			temp_var = malloc(sizeof(t_varlst));
			if(!temp_var)
				error(MALLOC,NULL);
			command = ft_split(input[j],'=');
			if(check_exist_env(data,command[0]))
				change_exist_env(data,command);
			else
			{
					temp_var->var_name = ft_mllstrcpy(command[0]);
					temp_var->var_value = ft_mllstrcpy(command[1]);
					temp_var->next = NULL;
					add_list(data,temp_var);
					temp_var = temp_var->next;
			}
			free_strings(command);
		}
	}
	free_strings(input);
}
