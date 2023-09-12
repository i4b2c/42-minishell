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
	input = ft_strtrim(temp, " \t");
	free(temp);
	return (input);
}

bool	check_pipes(char *str, int i)
{
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
		return (error("unexpected token", '|'));
	if (str[i] == '|' && str[i + 1] == '|')
		return (error("unexpected token", '|'));
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

bool	check_redirect(char *str, int i)
{
	if (str[i] != '>' && str[i] != '<')
		return (true);
	if (str[0] == '>' || str[0] == '<'
		|| str[ft_strlen(str) - 1] == '<' || str[ft_strlen(str) - 1] == '>')
		return (error("unexpected token", '>'));
	if ((str[i] == '<' && str[i + 1] == '>')
		|| (str[i] == '>' && str[i + 1] == '<'))
		return (error("unexpected token", '>'));
	if (str[i + 1] == '>' || str[i + 1] == '<')
	{
		if (str[i + 2] == '<' || str[i + 2] == '>')
			return (error("unexpected token", '>'));
	}
	return (true);
}

bool	check_quotes(char *str)
{
	int	i;

	i = 0;
	if (is_there_quotes(str) == false)
		return (true);
	while (str[i] && i >= 0)
	{
		if (str[i] == '\'')
			i = get_next_quote(str, i, '\'');
		else if (str[i] == '"')
			i = get_next_quote(str, i, '"');
		i++;
	}
	if (i < 0)
		return (error("'unclosed quotes'\n", '\0'));
	return (true);
}

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
