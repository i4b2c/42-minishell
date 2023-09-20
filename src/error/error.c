/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:22:49 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:22:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	error(char *str, char str_extra)
{
	write(2, str, ft_strlen(str));
	if (str_extra)
	{
		write(2, " ", 1);
		ft_putchar_fd(str_extra, STDERR_FILENO);
		write(2, "\n", 1);
	}
	return (false);
}
