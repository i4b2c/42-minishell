/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:18:55 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:18:55 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_statlst	*get_stat(int ac, char **av)
{
	t_statlst	*temp_stat;

	temp_stat = malloc(sizeof(t_statlst));
	if (!temp_stat)
		error(MALLOC, NULL);
	temp_stat->ac = ac;
	temp_stat->av = av;
	temp_stat->next = NULL;
	return (temp_stat);
}

t_varlst	*get_var(char **envp)
{
	t_varlst	*new_var;
	t_varlst	*head_var;
	t_varlst	*temp_var;
	int			num_strings;
	char		**var;

	num_strings = 0;
	head_var = NULL;
	temp_var = NULL;
	while (envp[num_strings])
	{
		new_var = malloc(sizeof(t_varlst));
		if (!new_var)
			error(MALLOC, NULL);
		var = ft_split(envp[num_strings], '=');
		new_var->var_name = ft_mllstrcpy(var[0]);
		if (!var[1])
			new_var->var_value = ft_mllstrcpy("");
		else
			new_var->var_value = ft_mllstrcpy(var[1]);
		new_var->next = NULL;
		if (!head_var)
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
	return (head_var);
}

t_data	*get_data(int ac, char **av, char **envp)
{
	t_data	*temp_data;

	temp_data = (t_data *)malloc(sizeof(t_data));
	if (!temp_data)
		error(MALLOC, NULL);
	temp_data->envp = envp;
	temp_data->stat_head = get_stat(ac, av);
	temp_data->var_head = get_var(envp);
	temp_data->check_out = false;
	temp_data->check_in = false;
	return (temp_data);
}
