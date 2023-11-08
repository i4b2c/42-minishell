/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:14:05 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:14:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_input(char *str)
{
	int	i;

	i = 0;
	if (!check_quotes(str))
		return (false);
	while (str[i])
	{
		if (str[i] == '\'')
			i = get_next_quote(str, i, '\'');
		else if (str[i] == '"')
			i = get_next_quote(str, i, '"');
		else
		{
			if (!check_redirect(str, i)
				|| !check_pipes(str, i) || !invalid_operator(str, i))
				return (false);
		}
		i++;
	}
	return (true);
}

bool	invalid_operator(char *str, int i)
{
	if (str[i] == '{' || str[i] == '}'
		|| str[i] == '(' || str[i] == ')'
		|| str[i] == '[' || str[i] == ']'
		|| str[i] == ';' || str[i] == '&' || str[i] == '*' || str[i] == '\\')
		return (error("unexpected tokens", str[i]));
	return (true);
}
