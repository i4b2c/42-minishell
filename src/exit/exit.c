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

void	unlink_all(void)
{
	unlink(TEMP_FILE_OUT);
	unlink(TEMP_FILE);
}

void	check_exit(t_data *data)
{
	long long	num_exit;

	num_exit = 0;
	write(STDOUT_FILENO, "exit\n", 5);
	if (data->tokens_head->next)
	{
		if (check_non_numeric(data->tokens_head->next->command))
		{
			write(STDERR_FILENO, "minishell: numeric argument required\n", 38);
			num_exit = 2;
		}
		else
			num_exit = ft_atoll(data->tokens_head->next->command);
	}
	if (len_data(data->tokens_head) > 2)
	{
		write(STDERR_FILENO, "minishell: too many arguments\n", 31);
		num_exit = 1;
	}
	free_data(&data);
	exit(num_exit);
}
