/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:28 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 16:15:17 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

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
		i++;
	}
	return (len);
}

char	*new_input(char *input)
{
	int		i_input;
	int		i_new;
	char	*new_input;

	i_input = 0;
	i_new = 0;
	new_input = malloc(((get_len_pipes(input) * 2) + 1 + ft_strlen(input)) * sizeof(char));
	while (input[i_input])
	{
		if (input[i_input] == '|')
		{
			new_input[i_new] = ' ';
			new_input[i_new + 1] = input[i_input];
			new_input[i_new + 2] = ' ';
			i_new += 2;
		}
		else
			new_input[i_new] = input[i_input];
		i_new++;
		i_input++;
	}
	new_input[i_new] = 0;
	free(input);
	return (new_input);
}

char	*ft_mllstrcat(char *str1, char *str2, char c)
{
	char	*temp;
	int		i1;
	int		i2;

	if (!str1)
		return (ft_mllstrcpy(str2));
	if (!c)
		temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	else
		temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
	i1 = -1;
	while (str1[++i1])
		temp[i1] = str1[i1];
	if (c)
		temp[i1++] = c;
	i2 = -1;
	while (str2[++i2])
		temp[i1 + i2] = str2[i2];
	temp[i1 + i2] = 0;
	return (temp);
}

char	*get_path(char *input, int *i)
{
	int		len;
	int		i_temp;
	char	*temp;

	temp = malloc(sizeof(char) * (i_temp - *i + 1));
	i_temp = *i;
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

char	*get_path_input(char *input, t_data *data)
{
    int		i;
	int		len;
	int		i_temp;
	char	*temp_path;
	char	*temp_input;

	i = 0;
	len = get_len_path(input, data);
	temp_input = malloc(sizeof(char) * len);
	len = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[0] != '\'')
		{
			temp_path = get_path(input, &i);
			temp_path = ft_getenv(temp_path, data);
			i_temp = 0;
			while (temp_path[i_temp])
			{
				temp_input[len] = temp_path[i_temp];
				i_temp++;
				len++;
			}
			free(temp_path);
		}
		else
		{
			temp_input[len] = input[i];
			len++;
			i++;
		}
	}
	temp_input[len] = 0;
	return (temp_input);
}

char	**cut_quote(char **tokens, t_data *data)
{
	int		i;
	char	*c_temp;

	i = 0;
	while (tokens[i])
	{
		tokens[i] = get_path_input(tokens[i],data);
		if (is_quote(tokens[i][0]))
		{
			c_temp = malloc(2);
			c_temp[0] = tokens[i][0];
			c_temp[1] = 0;
			tokens[i] = ft_strtrim(tokens[i], c_temp);
			free(c_temp);
		}
		i++;
	}
	return (tokens);
}

char	**split_input(char *input, t_data *data)
{
	int		input_len;
	char	**tokens;
	int		token_count;
	int		i;
	int		start;
	char	quote_type;

	token_count = 0;
	i = 0;
	input_len = ft_strlen(input);
	tokens = malloc(sizeof(char *) * (input_len + 1));
	while (i < input_len)
	{
		while (i < input_len && input[i] == ' ')
			i++;

		if (i == input_len)
			break;
		start = i;
		if (is_quote(input[i]))
		{
			quote_type = input[i];
			i++;
			while (i < input_len && input[i] != quote_type)
				i++;
			tokens[token_count] = strndup(input + start, i - start + 1);
			token_count++;
			i++;
		}
		else
		{
			while (i < input_len && input[i] != ' ' && !is_quote(input[i]))
				i++;
			tokens[token_count] = strndup(input + start, i - start);
			token_count++;
		}
	}
	tokens[token_count] = NULL;
	return (cut_quote(tokens,data));
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*input;
	int		temp_stdout;
	int		temp_stdin;
	char	**input_split;

	if (ac > 1 && av)
		error(ARGS, NULL);
	data = get_data(ac, av, envp);
	init_signal();
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while (1)
	{
		dup2(temp_stdout, STDOUT_FILENO);
		dup2(temp_stdin, STDIN_FILENO);
		input = get_input();
		if (!input[0])
			free(input);
		else
		{
			add_history(input);
			input = new_input(input);
			input_split = split_input(input, data);
			data->tokens_head = tokens_input(input_split, data);
			if(!strncmp(data->tokens_head->command, "exit", 4))
			{
				free_data(&data);
				break ;
			}
			exec_tokens(data);
			unlink(TEMP_FILE);
			free_tokens(data);
		}
	}
	return (0);
}
