/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 01:52:29 by marvin            #+#    #+#             */
/*   Updated: 2023/08/12 01:52:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void free_strings(char **str)
{
	int i;

	i = 0;
	while(str[i])
		free(str[i++]);
	free(str);
}

void free_data(t_data **data)
{
	t_varlst *temp_var;
	t_statlst *temp_stat;

	while((*data)->var_head != NULL)
	{
		temp_var = (*data)->var_head->next;
		free((*data)->var_head->var_name);
		free((*data)->var_head->var_value);
		free((*data)->var_head);
		(*data)->var_head = temp_var;
	}
	while((*data)->stat_head != NULL)
	{
		temp_stat = (*data)->stat_head->next;
		free((*data)->stat_head);
		(*data)->stat_head = temp_stat;
	}
	free(*data);
	*data = NULL;
}

void free_tokens(t_data *data)
{
	t_tokens *temp_tokens;

	while(data->tokens_head != NULL)
	{
		temp_tokens = data->tokens_head->next;
		free(data->tokens_head->command);
		free(data->tokens_head);
		data->tokens_head = temp_tokens;
	}
	data->tokens_head = NULL;
}
