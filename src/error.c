/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:27:19 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:27:19 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error(char *str, char *str_extra)
{
	write(2, str, ft_strlen(str));
	if (str_extra)
	{
		write(2, str_extra, ft_strlen(str_extra));
		write(2, "\n", 1);
	}
	return ;
}
