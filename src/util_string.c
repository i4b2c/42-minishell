/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:20:57 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 16:20:57 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len_strings(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	print_string(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_printf("%s\n", str[i++]);
}

char	check_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			break ;
		i++;
	}
	return (str[i]);
}
