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

extern volatile long long	g_exit_status;

void	unlink_all(void)
{
	unlink(TEMP_FILE_OUT);
	unlink(TEMP_FILE);
}

void	end_exit(t_data *data, char *input)
{
	free(input);
	unlink_all();
	free_tokens(data);
	exit(g_exit_status);
}

void	check_exit(t_data *data, char *input)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (data->tokens_head->next)
	{
		if (check_non_numeric(data->tokens_head->next->command))
		{
			write(STDERR_FILENO, "minishell: numeric argument required\n", 38);
			g_exit_status = 2;
			end_exit(data, input);
		}
		else if (len_data(data->tokens_head) > 2)
		{
			write(STDERR_FILENO, "minishell: too many arguments\n", 31);
			g_exit_status = 1;
			return ;
		}
		else
			g_exit_status = ft_atoll(data->tokens_head->next->command);
	}
	free_data(&data);
	exit(g_exit_status);
}
