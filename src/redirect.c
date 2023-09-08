/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:15:29 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 16:15:29 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	change_stdout(char *str, t_type type)
{
	int	fd;

	if (type == RDR_OUT)
	{
		unlink(str);
		fd = open(str, O_WRONLY | O_CREAT, 0666);
	}
	else if (type == RDR_AP_OUT)
		fd = open(str, O_WRONLY | O_CREAT, 0666 | O_APPEND);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

void	change_stdin(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	dup2(fd, STDIN_FILENO);
}
