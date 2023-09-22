/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:21:28 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 14:21:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*cut_quotes_all(char *input)
{
	char	*output;
	int		output_index;
	bool	inside_single_quotes;
	bool	inside_double_quotes;
	int		i;

	inside_double_quotes = false;
	inside_single_quotes = false;
	output_index = 0;
	output = malloc(ft_strlen(input) + 1);
	i = -1;
	while (++i < ft_strlen(input))
	{
		if (input[i] == '\'' && !inside_double_quotes)
			inside_single_quotes = !inside_single_quotes;
		else if (input[i] == '"' && !inside_single_quotes)
			inside_double_quotes = !inside_double_quotes;
		else
			output[output_index++] = input[i];
	}
	free(input);
	output[output_index] = '\0';
	return (output);
}
