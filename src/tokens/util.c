/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:11:23 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:11:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_there_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
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
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (-2);
	return (i);
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

void	get_type_input(t_tokens *temp)
{
	int		len_string;

	while (temp)
	{
		len_string = ft_strlen(temp->command);
		if (temp->command[0] == '<'
			&& temp->command[1] == '<' && len_string == 2)
			temp->next->type = RDR_RD_IN;
		else if (temp->command[0] == '<' && len_string == 1)
			temp->next->type = RDR_IN;
		else if (temp->command[0] == '>' && len_string == 1)
			temp->next->type = RDR_OUT;
		else if (temp->command[0] == '>'
			&& temp->command[1] == '>' && len_string == 2)
			temp->next->type = RDR_AP_OUT;
		else if (temp->command[0] == '|' && len_string == 1)
			temp->type = PIPE;
		temp = temp->next;
	}
}

void	remove_node(t_tokens **head, t_tokens *node_to_remove)
{
	t_tokens	*prev;

	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = (*head)->next;
		free(node_to_remove);
		return ;
	}
	prev = *head;
	while (prev->next != NULL && prev->next != node_to_remove)
		prev = prev->next;
	if (prev->next == node_to_remove)
	{
		prev->next = node_to_remove->next;
		free(node_to_remove);
	}
}
