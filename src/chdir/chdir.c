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

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

bool	check_extra_chdir(char *str)
{
	char	**temp;
	int		len;

	temp = ft_split(str, ' ');
	len = len_strings(temp);
	free_strings(temp);
	free(temp);
	if (len > 1)
		return (true);
	return (false);
}

void	exec_chdir(char **input)
{
	if (len_strings(input) > 2 || check_extra_chdir(input[1]))
	{
		write(2, "minishell: too many arguments\n", 30);
		g_exit_status = 1;
		return ;
	}
	else if (chdir(input[1]) != 0)
	{
		perror("minishell ");
		g_exit_status = 1;
		return ;
	}
	return ;
}
