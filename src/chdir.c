/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:12:03 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:12:03 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern long long g_exit_status;

void	exec_chdir(char **input)
{
	if (len_strings(input) > 2)
	{
		write(2, "minishell: too many arguments\n", 30);
		g_exit_status = 1;
	}
	else if (chdir(input[1]) != 0)
	{
		perror("minishell ");
		g_exit_status = 1;
	}
	free_strings(input);
	return ;
}
