/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:59:26 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 12:59:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_len_pipes(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '|')
			len++;
		else if (input[i] == '<' || input[i] == '>')
			len++;
		i++;
	}
	return (len);
}

int	len_data(t_tokens *tokens)
{
	int	i;

	i = 0;
	while (tokens)
	{
		tokens = tokens->next;
		i++;
	}
	return (i);
}
