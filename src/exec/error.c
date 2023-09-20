/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:17:42 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:17:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

int	error_dir(char **command)
{
	g_exit_status = 126;
	write(2, "minishell : Is a directory\n", 28);
	free_strings(command);
	return (g_exit_status);
}

int	error_nf(char **command)
{
	write(2, "minishell : command not found\n", 30);
	g_exit_status = 127;
	free_strings(command);
	return (g_exit_status);
}

int	error_access(char **command)
{
	perror("minishell");
	g_exit_status = 126;
	free_strings(command);
	return (g_exit_status);
}
