/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:04:39 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:04:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	change_double_input(char *new_input,
	char *input, int *i_new, int *i_input)
{
	new_input[*i_new] = ' ';
	new_input[(*i_new) + 1] = input[*i_input];
	new_input[(*i_new) + 2] = input[*i_input];
	new_input[(*i_new) + 3] = ' ';
	(*i_input)++;
	(*i_new) += 3;
}

void	change_simple_input(char *new_input,
	char *input, int *i_new, int i_input)
{
	new_input[(*i_new)] = ' ';
	new_input[(*i_new) + 1] = input[i_input];
	new_input[(*i_new) + 2] = ' ';
	(*i_new) += 2;
}
