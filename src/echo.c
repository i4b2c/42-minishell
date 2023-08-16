#include "../include/minishell.h"

int search_envp(t_data *data, char *cmd)
{
	t_varlst *temp_var;

	temp_var = data->var_head;
	while(temp_var)
	{
		if(!strncmp(temp_var->var_name,cmd+1,ft_strlen(cmd)-1))
		{
			ft_printf("%s",temp_var->var_value);
			return 1;
		}
		temp_var = temp_var->next;
	}
	return 0;
}

void exec_echo(t_data *data, char **input)
{
	char *temp;
	int i;

	i = 0;
	while(input[++i])
	{
		temp = ft_strtrim(input[i],"\"");
		if(temp[0] == '$')
		{
			if(search_envp(data,temp)
				&& input[i+1])
				write(STDOUT_FILENO," ",1);
		}
		else
		{
			ft_printf("%s",temp);
			if(input[i+1])
				write(STDOUT_FILENO," ",1);
		}
		free(temp);
	}
	write(STDOUT_FILENO,"\n",1);
	free_strings(input);
}
