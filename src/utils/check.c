/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:01:57 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:01:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	check_non_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0)
		{
			if (!(str[i] >= '0' && str[i] <= '9'))
				return (true);
		}
		else
		{
			if (!(str[i] >= '0' && str[i] <= '9')
				&& str[i] != '-' && str[i] != '+')
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_pipes(char *str, int i)
{
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
		return (error("unexpected token", '|'));
	if (str[i] == '|' && str[i + 1] == '|')
		return (error("unexpected token", '|'));
	return (true);
}

bool	check_closed_quotes(const char *input, int i_str)
{
	bool	inside_quotes;
	char	current_quote;
	int		i;

	inside_quotes = false;
	current_quote = '\0';
	i = 0;
	while (i < i_str)
	{
		if (!inside_quotes && (input[i] == '\'' || input[i] == '"'))
		{
			inside_quotes = true;
			current_quote = input[i];
		}
		else if (inside_quotes && input[i] == current_quote)
			inside_quotes = false;
		i++;
	}
	return (inside_quotes);
}
