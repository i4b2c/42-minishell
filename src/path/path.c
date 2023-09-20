/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:25:00 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:25:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

char	*get_path(char *input, int *i)
{
	int		len;
	int		i_temp;
	char	*temp;

	i_temp = *i;
	temp = malloc(sizeof(char) * (i_temp - *i + 1));
	len = 0;
	(*i)++;
	while (input[i_temp] && isalnum(input[i_temp]))
		i_temp++;
	while (input[*i] && isalnum(input[*i]))
	{
		temp[len] = input[*i];
		(*i)++;
		len++;
	}
	temp[len] = '\0';
	return (temp);
}

int	get_len_path(char *input, t_data *data)
{
	int		len;
	int		i;
	char	*temp_path;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			temp_path = get_path(input, &i);
			temp_path = ft_getenv(temp_path, data);
			len += ft_strlen(temp_path);
			free(temp_path);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len + 1);
}

void	path_echo_exit(char *temp_input, int *len, int *i)
{
	int		i_int_temp;
	char	*temp_int;

	i_int_temp = 0;
	temp_int = ft_itoa(g_exit_status);
	while (temp_int[i_int_temp])
	{
		temp_input[*len] = temp_int[i_int_temp];
		i_int_temp++;
		(*len)++;
	}
	(*i) += 2;
	free(temp_int);
}

void	path_echo(t_data *data, char *temp_input, int *i, int *len)
{
	int		i_temp;
	char	*temp_path;

	temp_path = get_path(data->input, i);
	temp_path = ft_getenv(temp_path, data);
	i_temp = 0;
	while (temp_path[i_temp])
	{
		temp_input[(*len)] = temp_path[i_temp];
		i_temp++;
		(*len)++;
	}
	free(temp_path);
}

char	*get_path_input(char *input, t_data *data)
{
	int		i;
	int		len;
	int		i_temp;
	char	*temp_input;

	temp_input = malloc(sizeof(char) * get_len_path(input, data));
	data->input = ft_mllstrcpy(input);
	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '?' && input[0] != '\'')
			path_echo_exit(temp_input, &len, &i);
		else if (input[i] == '$' && !ft_isalnum(input[i + 1]))
		{
			temp_input[len++] = '$';
			i++;
		}
		else if (input[i] == '$' && input[0] != '\'')
			path_echo(data, temp_input, &i, &len);
		else
			temp_input[len++] = input[i++];
	}
	temp_input[len] = 0;
	return (temp_input);
}
