/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:21:18 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 16:21:18 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_mllstrcpy(char *str)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(str);
	temp = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

void	add_list(t_data *data, t_varlst *temp_var)
{
	t_varlst	*atual;

	atual = NULL;
	if (data->var_head == NULL)
		data->var_head = temp_var;
	else
	{
		atual = data->var_head;
		while (atual->next != NULL)
			atual = atual->next;
		atual->next = temp_var;
	}
}

bool	is_there_quotes(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

int	get_next_quote(char *str, int begin, char quote)
{
	int	i;
	i = begin + 1;
	while(str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (-2);
	return (i);
}

void	cntr_d(char *input, t_data **data)
{
	if (!input)
	{
		rl_clear_history();
		ft_putendl_fd("exit", STDOUT_FILENO);
		free_data(data);
		exit(EXIT_SUCCESS);
	}
}
