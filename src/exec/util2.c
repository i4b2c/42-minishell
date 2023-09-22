/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:16:26 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:16:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_string(t_tokens *tokens)
{
	t_tokens	*temp;
	int			pipe;

	temp = tokens;
	pipe = 0;
	while (temp)
	{
		if (temp->type == PIPE)
			pipe++;
		temp = temp->next;
	}
	return (pipe);
}

char	*check_command(char *command, char **path)
{
	char	*teste;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		teste = malloc(256);
		ft_strcpy(teste, path[i]);
		ft_strlcat(teste, "/", 256);
		ft_strlcat(teste, command, 256);
		if (access(teste, X_OK) == 0)
			return (teste);
		i++;
		free(teste);
	}
	return (NULL);
}

char	*ft_getenv(char *str, t_data *data, bool op)
{
	t_varlst	*temp_var;

	temp_var = data->var_head;
	while (temp_var)
	{
		if (!strncmp(temp_var->var_name, str,
				ft_strlen((char *)temp_var->var_name)))
		{
			if (op == true)
				free(str);
			return (ft_mllstrcpy(temp_var->var_value));
		}
		temp_var = temp_var->next;
	}
	if (op == true)
		free(str);
	return (ft_calloc(1, 1));
}
