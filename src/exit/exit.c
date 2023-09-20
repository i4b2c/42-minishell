/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:00:43 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:00:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_exit(t_data *data)
{
	long long	num_exit;

	if (len_data(data->tokens_head) > 2)
	{
		free_data(&data);
		write(2, "minishell: too many arguments\n", 31);
		exit(1);
	}
	else if (data->tokens_head->next)
	{
		if (check_non_numeric(data->tokens_head->next->command))
		{
			write(2, "minishell: numeric argument required\n", 38);
			free_data(&data);
			exit(2);
		}
		num_exit = ft_atoll(data->tokens_head->next->command);
		free_data(&data);
		exit((int)num_exit);
	}
	else
	{
		free_data(&data);
		exit(0);
	}
}
