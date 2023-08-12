/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 01:52:59 by marvin            #+#    #+#             */
/*   Updated: 2023/08/12 01:52:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_input(void)
{
	char *input;

	input = readline("\033[0;32mminishell $>\033[0m ");
	if(input[0] == '|' || input[0] == '}'
		|| input[0] == '&' || input[0] == ')'
		|| input[0] == ']')
			error(INPUT,input);
	else if(input[0] == '>' || input[0] == '<')
		error(INPUT_NEW_LINE,NULL);
	return (input);
}
