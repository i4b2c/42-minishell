#include "../include/minishell.h"

int num_data_env(t_data *data)
{
	int i;
	t_varlst *temp;

	i = 0;
	temp = data->var_head;
	while(temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return i;
}

char *copy_var(t_varlst *temp)
{
	int len_var;
	int len_value;
	char *temp_envp;

	len_var = 0;
	len_value = 0;
	while(temp->var_name[len_var])
		len_var++;
	while(temp->var_value[len_value])
		len_value++;
	temp_envp = malloc(sizeof(char) * (len_var + len_value + 2));
	len_var = 0;
	while(temp->var_name[len_var])
	{
		temp_envp[len_var] = temp->var_name[len_var];
		len_var++;
	}
	temp_envp[len_var] = '=';
	len_value = 0;
	while(temp->var_value[len_value])
	{
		temp_envp[len_value+1+len_var] = temp->var_value[len_value];
		len_value++;
	}
	temp_envp[len_value+1+len_var] = 0;
	return temp_envp;
}

char **replicate_string(t_data *data)
{
	char **temp_envp;
	int num_string;
	int i;
	t_varlst *temp;

	num_string = 0;
	while(data->envp[num_string])
		num_string++;
	temp_envp = malloc(sizeof(char *) * (num_string + 1 + num_data_env(data)));
	i = 0;
	while(i < num_string)
	{
		temp_envp[i] = malloc(ft_strlen(data->envp[i]) + 1);
		ft_strcpy(temp_envp[i],data->envp[i]);
		i++;
	}
	temp = data->var_head;
	while(temp != NULL)
	{
		//temp_envp[i] = malloc(ft_strlen(temp->var_name) + ft_strlen(temp->var_value) + 2);
		temp_envp[i] = copy_var(temp);
		// ft_strlcat(temp_envp[i],temp->var_name,ft_strlen(temp->var_name)-1);
		// ft_strlcat(temp_envp[i],"=",1);
		// ft_strlcat(temp_envp[i],temp->var_value,ft_strlen(temp->var_value));
		temp = temp->next;
		i++;
	}
	temp_envp[i] = NULL;
	return temp_envp;
}

void sort_string(char **str)
{
	int num_string;
	int i;
	int j;
	char *temp;

	num_string = 0;
	while(str[num_string])
		num_string++;
	i = 0;
	while(i < num_string - 1)
	{
		j = 0;
		while(j < num_string - i - 1)
		{
			if(strcmp(str[j],str[j+1]) > 0)
			{
				temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
			j++;
		}
		i++;
	}
}


void print_export(t_data *data)
{
	char **temp_str;

	temp_str = replicate_string(data);
	sort_string(temp_str);
	print_string(temp_str);
	free_strings(temp_str);
}
