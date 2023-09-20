/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:28 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/20 13:09:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

void	minishell(t_data *data, int ac, char **av, char **envp)
{
	char	*input;

	data = get_data(ac, av, envp);
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
			add_history(input);
			input = new_input(input);
			data->tokens_head = get_tokens(data, input);
			if (!strncmp(data->tokens_head->command, "exit", 4))
				check_exit(data);
			exec_tokens(data);
			free(input);
			unlink(TEMP_FILE);
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
		minishell(data, ac, av, envp);
	return (0);
}
