/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:19:45 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:19:45 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	search_envp(t_data *data, char *cmd)
{
	t_varlst	*temp_var;

	temp_var = data->var_head;
	while (temp_var)
	{
		if (!strncmp(temp_var->var_name, cmd + 1, ft_strlen(cmd) - 1))
		{
			ft_printf("%s", temp_var->var_value);
			return (1);
		}
		temp_var = temp_var->next;
	}
	return (0);
}

/*
char	*clean_str(char *str)
{
	int i = -1;
	int	quotes_num;
	int	j;
	char *temp;

	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			quotes_num += 1;
	}
	//temp = malloc(sizeof(char) * i - quotes_num + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i++;
		if (!str[i])
			break ;
		temp[j] = str[i];
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

void	final_quote_check(char *str)
{
	int i = 0;
	int j = 0;
	char *temp;
	if (str[i] == '\'' || str[i] == '"')
		return ;
	while (str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	if ((str[i] == '\'' && str[i + 1] == '"') || (str[i] == '"' && str[i + 1] == '\''))
		i++;
	else if (str[i] == '\'' || str[i] == '"')
	{
		str = clean_str(str);
	}
}
*/

void	exec_echo(t_data *data, char **input)
{
	// t_tokens *temp;

	// temp = data->tokens_head;
	// while(temp)
	// {

	// }
	char	*temp;
	int		i;

	i = 0;
	while (input[++i])
	{
		temp = ft_strtrim(input[i], "\"");
		if (temp[0] == '$')
		{
			if (search_envp(data, temp)
				&& input[i + 1])
				write(STDOUT_FILENO, " ", 1);
		}
		else
		{
			//if (is_there_quotes(temp))
				//final_quote_check(temp);
			ft_printf("%s", temp);
			if (input[i + 1])
				write(STDOUT_FILENO, " ", 1);
		}
		free(temp);
	}
	write(STDOUT_FILENO, "\n", 1);
	free_strings(input);
}
