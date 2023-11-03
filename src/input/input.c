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

#include "../../include/minishell.h"

char	*get_input(void)
{
	char	*input;
	char	*temp;

	temp = readline("\033[0;32mminishell $>\033[0m ");
	input = ft_strtrim(temp, " \t");
	free(temp);
	add_history(input);
	return (input);
}

char	*new_input(char *input)
{
	int		i_input;
	int		i_new;
	char	*new_input;

	i_input = -1;
	i_new = 0;
	new_input = malloc(((get_len_pipes(input) * 2) + 1 + ft_strlen(input)));
	while (input[++i_input])
	{
		if ((input[i_input] == '<' && input[i_input + 1] == '<'
				&& !check_closed_quotes(input, i_input))
			|| (input[i_input] == '>' && input[i_input + 1] == '>'
				&& !check_closed_quotes(input, i_input)))
			change_double_input(new_input, input, &i_new, &i_input);
		else if ((input[i_input] == '|' && !check_closed_quotes(input, i_input))
			|| (input[i_input] == '>' && !check_closed_quotes(input, i_input))
			|| (input[i_input] == '<' && !check_closed_quotes(input, i_input)))
			change_simple_input(new_input, input, &i_new, i_input);
		else
			new_input[i_new] = input[i_input];
		i_new++;
	}
	new_input[i_new] = 0;
	free(input);
	return (new_input);
}
