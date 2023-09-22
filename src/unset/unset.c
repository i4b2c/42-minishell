/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:19:55 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 16:19:55 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

void	free_unset(t_varlst *temp, t_varlst *temp_var)
{
	temp = temp_var->next->next;
	free(temp_var->next->var_name);
	free(temp_var->next->var_value);
	free(temp_var->next);
	temp_var->next = temp;
}

void	exec_unset(t_data *data, char **input)
{
	t_varlst	*temp_var;
	t_varlst	*temp;
	int			i;

	i = 0;
	while (input[++i])
	{
		if (check_input_env(input[i]))
		{
			write(2, "not a valid identifier\n", 24);
			g_exit_status = 1;
		}
		temp_var = data->var_head;
		while (temp_var)
		{
			if (temp_var->next && !strncmp(temp_var->next->var_name,
					input[i], ft_strlen(input[i])))
			{
				free_unset(temp, temp_var);
				break ;
			}
			temp_var = temp_var->next;
		}
	}
}
