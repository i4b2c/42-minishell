#include "../include/minishell.h"

void error(char *str,char *str_extra)
{
	write(2,str,ft_strlen(str));
	if(str_extra)
	{
		write(2,str_extra,ft_strlen(str_extra));
		write(2,"\n",1);
	}
	//exit(EXIT_FAILURE);
	return ;
}

t_statlst *get_stat(int ac, char **av)
{
	t_statlst *temp_stat;

	temp_stat = malloc(sizeof(t_statlst));
	if(!temp_stat)
		error(MALLOC,NULL);
	temp_stat->ac = ac;
	temp_stat->av = av;
	temp_stat->next = NULL;
	return (temp_stat);
}

t_varlst *get_var(char **envp)
{
	t_varlst *new_var;
	t_varlst *head_var;
	t_varlst *temp_var;
	int num_strings;
	char **var;

	num_strings = 0;
	head_var = NULL;
	temp_var = NULL;
	while(envp[num_strings])
	{
		new_var = malloc(sizeof(t_varlst));
		if(!new_var)
			error(MALLOC,NULL);
		var = ft_split(envp[num_strings],'=');
		new_var->var_name = malloc(sizeof(char) * (ft_strlen(var[0]) + 1));
		ft_strcpy(new_var->var_name,var[0]);
		if(!var[1])
		{
			new_var->var_value = malloc(1);
			new_var->var_value[0] = 0;
		}
		else
		{
			new_var->var_value = malloc(sizeof(char) * (ft_strlen(var[1]) + 1));
			ft_strcpy(new_var->var_value,var[1]);
		}
		new_var->next = NULL;
		if(!head_var)
		{
			head_var = new_var;
			temp_var = head_var;
		}
		else
		{
			temp_var->next = new_var;
			temp_var = temp_var->next;
		}
		num_strings++;
	}
	return head_var;
}

t_data *get_data(int ac, char **av, char **envp)
{
	t_data *temp_data;

	temp_data = (t_data *)malloc(sizeof(t_data));
	if(!temp_data)
		error(MALLOC,NULL);
	temp_data->envp = envp;
	temp_data->stat_head = get_stat(ac, av);
	temp_data->var_head = get_var(envp);
	//temp_data->var_head->next = NULL;
	return (temp_data);
}
