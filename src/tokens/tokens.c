/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:16:58 by icaldas           #+#    #+#             */
/*   Updated: 2023/11/01 19:23:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

int	add_token(t_tokens **head, char *str, t_type type)
{
	t_tokens	*new_token;
	t_tokens	*temp;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return (-1);
	if (!str)
		new_token->command = NULL;
	else
		new_token->command = ft_strdup(str);
	new_token->type = type;
	new_token->next = NULL;
	if (!(*head))
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	return (0);
}

t_tokens	*final_tokens(t_data *data)
{
	t_tokens	*temp2;
	t_tokens	*temp;

	temp = NULL;
	temp2 = data->tokens_head;
	while (temp2->next)
	{
		if (temp2->next->type == NORMAL || temp2->next->type == PIPE)
			add_token(&temp, temp2->command, temp2->type);
		temp2 = temp2->next;
	}
	add_token(&temp, temp2->command, temp2->type);
	return (temp);
}

t_tokens	*get_tokens(t_data *data, char *str)
{
	int			i;
	t_tokens	*temp;

	i = -1;
	while (str[++i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		i = get_word_until(str, i, &data->tokens_head);
		if (str[i] == '\0')
			break ;
	}
	get_type_input(data->tokens_head);
	remove_quotes(data->tokens_head, data);
	temp = final_tokens(data);
	free_tokens(data);
	return (temp);
}
