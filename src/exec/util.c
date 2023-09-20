/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:15:59 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 13:15:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_tokens(t_tokens *head)
{
	int	res;

	res = 0;
	while (head)
	{
		res++;
		head = head->next;
	}
	return (res);
}

bool	choose_redirect(int *i,
	char **command, t_tokens *temp, t_data *data)
{
	if (temp->type == NORMAL)
		command[(*i)++] = ft_mllstrcpy(temp->command);
	else if (temp->type == RDR_OUT || temp->type == RDR_AP_OUT)
	{
		data->check_out = true;
		temp->fd_out = change_stdout(temp->command, temp->type);
	}
	else if (temp->type == RDR_IN)
	{
		data->check_in = true;
		if (!change_stdin(temp->command))
			return (false);
	}
	else if (temp->type == RDR_RD_IN)
	{
		data->check_in = true;
		read_stdin(temp->command, data->fd_in);
	}
	else if (temp->type == PIPE)
	{
		data->check_pipe = true;
		command = exec_pipe(data, command, len_tokens(data->tokens_head), *i);
		(*i) = 0;
	}
	return (true);
}

void	last_fd(t_data *data)
{
	int	fd_temp;

	dup2(data->fd_in, STDIN_FILENO);
	fd_temp = open(TEMP_FILE_OUT, O_RDONLY);
	if (fd_temp == -1)
		fd_temp = open(TEMP_FILE_OUT, O_CREAT | O_RDONLY);
	dup2(fd_temp, STDIN_FILENO);
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

char	*cut_quotes(char *input, char quote)
{
	char	*temp;
	int		i;
	int		i_temp;

	i = 0;
	i_temp = 0;
	temp = malloc(sizeof(char) * ft_strlen(input));
	while (input[i])
	{
		if (input[i] != quote)
		{
			temp[i_temp] = input[i];
			i_temp++;
		}
		i++;
	}
	temp[i_temp] = 0;
	return (temp);
}
