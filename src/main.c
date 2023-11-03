/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:28 by icaldas           #+#    #+#             */
/*   Updated: 2023/11/02 14:44:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

void	minishell(t_data *data, char **envp)
{
	char	*input;

	data = get_data(envp);
	init_signal();
	while (1)
	{
		dup2(data->fd_out, STDOUT_FILENO);
		dup2(data->fd_in, STDIN_FILENO);
		input = get_input();
		cntr_d(input, &data);
		if (!input[0] || !check_input(input))
			free(input);
		else
		{
			input = new_input(input);
			data->tokens_head = get_tokens(data, input);
			if (!ft_strncmp(data->tokens_head->command, "exit", 5))
				check_exit(data);
			else
				exec_tokens(data);
			free(input);
			unlink_all();
			free_tokens(data);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data			*data;

	data = NULL;
	if (ac > 1 && av)
		error(ARGS, '\0');
	else
		minishell(data, envp);
	return (0);
}
