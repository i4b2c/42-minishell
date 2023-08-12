#include "../include/minishell.h"

void error(char *str,char *str_extra)
{
	write(2,str,ft_strlen(str));
	if(str_extra)
		write(2,str_extra,ft_strlen(str_extra));
	exit(EXIT_FAILURE);
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

t_data *get_data(int ac, char **av, char **envp)
{
	t_data *temp_data;
	(void)ac;
	(void)av;

	temp_data = (t_data *)malloc(sizeof(t_data));
	if(!temp_data)
		error(MALLOC,NULL);
	temp_data->envp = envp;
	temp_data->stat_head = get_stat(ac, av);
	temp_data->var_head = NULL;
	return (temp_data);
}
