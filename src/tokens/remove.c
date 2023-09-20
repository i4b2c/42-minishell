/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:28:01 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:28:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_unquoted_size(char *str, char quote)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != quote)
			len++;
		i++;
	}
	return (len);
}

char	*remove_single_quotes(char *str)
{
	int		i;
	int		j;
	char	*quotes_free;
	int		size;

	i = 0;
	j = 0;
	size = get_unquoted_size(str, '\'');
	quotes_free = malloc(sizeof(char) * size + 1);
	while (str[i])
	{
		while (str[i] == '\'')
			i++;
		if (str[i] == '\0')
			break ;
		quotes_free[j] = str[i];
		i++;
		j++;
	}
	quotes_free[j] = '\0';
	return (quotes_free);
}

char	*remove_double_quotes(char *str)
{
	int		i;
	int		j;
	char	*quotes_free;
	int		size;

	i = 0;
	j = 0;
	size = get_unquoted_size(str, '"');
	quotes_free = malloc(sizeof(char) * size + 1);
	while (str[i])
	{
		while (str[i] == '"')
			i++;
		if (str[i] == '\0')
			break ;
		quotes_free[j] = str[i];
		i++;
		j++;
	}
	quotes_free[j] = '\0';
	return (quotes_free);
}
