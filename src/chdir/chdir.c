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

void	exec_cd_home(t_data *data)
{
	char	*home;

	home = ft_getenv("HOME", data, false);
	if (home[0] == 0)
	{
		write(2, "minishell : cd: HOME not set\n", 29);
		free(home);
		g_exit_status = 1;
		return ;
	}
	else
		chdir(home);
	free(home);
}

void	exec_chdir(char **input, t_data *data)
{
	if (len_strings(input) == 1)
		exec_cd_home(data);
	else if (len_strings(input) > 2 || check_extra_chdir(input[1]))
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
