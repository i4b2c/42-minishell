/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:24:24 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:24:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_head_quotes(t_tokens *head, t_data *data)
{
	if (is_there_quotes(head->command))
	{
		if (head->command[0] == '\'')
			head->command = remove_single_quotes(head->command);
		else if (head->command[0] == '"')
		{
			head->command = get_path_input(head->command, data);
			free(data->input);
			head->command = remove_double_quotes(head->command);
		}
	}
	else
		return ;
}

void	remove_quotes(t_tokens *head, t_data *data)
{
	while (head != NULL)
	{
		if (head->command[0] != '\'')
			head->command = get_path_input(head->command, data);
		free(data->input);
		data->input = NULL;
		head->command = cut_quotes_all(head->command);
		head = head->next;
	}
}

int	get_word_until(char *str, int i, t_tokens **head)
{
	int		begin;
	int		checker;
	char	*temp;

	begin = i;
	while (str[i])
	{
		if (is_there_token(str[i] != NORMAL) || str[i] == ' ' || str[i] == '\t')
			break ;
		if (str[i] == '\'')
			i = get_next_quote(str, i, '\'');
		else if (str[i] == '"')
			i = get_next_quote(str, i, '"');
		i++;
	}
	temp = ft_substr(str, begin, i - begin);
	checker = add_token(head, temp, NORMAL);
	free(temp);
	if (checker == (-1))
		return (checker);
	return (i);
}

int	get_new_token(char *str, int i, t_tokens **head)
{
	int	checker;

	checker = -1;
	if (str[i] == '<' && str[i + 1] == '<')
	{
		checker = add_token(head, NULL, RDR_RD_IN);
		i += 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		checker = add_token(head, NULL, RDR_AP_OUT);
		i += 1;
	}
	else if (str[i] == '<')
		checker = add_token(head, NULL, RDR_IN);
	else if (str[i] == '>')
		checker = add_token(head, NULL, RDR_OUT);
	else if (str[i] == '|')
		checker = add_token(head, NULL, PIPE);
	if (checker == (-1))
		return (checker);
	return (i);
}

t_type	is_there_token(char c)
{
	if (c == '<')
		return (RDR_IN);
	if (c == '>')
		return (RDR_OUT);
	if (c == '|')
		return (PIPE);
	return (NORMAL);
}
