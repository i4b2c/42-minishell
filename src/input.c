/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:50:34 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:50:34 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_input(void)
{
	char	*input;
	char	*temp;

	temp = readline("\033[0;32mminishell $>\033[0m ");
	if (temp[0] == '|' || temp[0] == '}'
		|| temp[0] == '&' || temp[0] == ')'
		|| temp[0] == ']')
	{
		error(INPUT, temp);
		free(temp);
		return (NULL);
	}
	else if (temp[0] == '>' || temp[0] == '<')
	{
		error(INPUT_NEW_LINE, NULL);
		free(temp);
		return (NULL);
	}
	input = ft_strtrim(temp, " \t");
	free(temp);
	return (input);
}
