/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:10:24 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:10:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(t_data *data)
{
	t_varlst	*temp_var;

	temp_var = data->var_head;
	while (temp_var != NULL)
	{
		ft_printf("%s=%s\n", temp_var->var_name, temp_var->var_value);
		temp_var = temp_var->next;
	}
}
