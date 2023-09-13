/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:28 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/13 15:48:26 by icaldas          ###   ########.fr       */
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
		else if (input[i] == '<' || input[i] == '>')
			len++;
		i++;
	}
	return (len);
}

bool	check_closed_quotes(const char *input, int i_str)
{
	bool	inside_quotes;
	char	current_quote;
	int		i;

	inside_quotes = false;
	current_quote = '\0';
	i = 0;
	while (i < i_str)
	{
		if (!inside_quotes && (input[i] == '\'' || input[i] == '"'))
		{
			inside_quotes = true;
			current_quote = input[i];
		}
		else if (inside_quotes && input[i] == current_quote)
			inside_quotes = false;
		i++;
	}
	return (inside_quotes);
}

char	*new_input(char *input)
{
	int		i_input;
	int		i_new;
	char	*new_input;

	i_input = 0;
	i_new = 0;
	new_input = malloc(((get_len_pipes(input) * 2)
				+ 1 + ft_strlen(input)) * sizeof(char));
	while (input[i_input])
	{
		if ((input[i_input] == '<' && input[i_input + 1] == '<'
				&& !check_closed_quotes(input, i_input))
			|| (input[i_input] == '>' && input[i_input + 1] == '>'
				&& !check_closed_quotes(input, i_input)))
		{
			new_input[i_new] = ' ';
			new_input[i_new + 1] = input[i_input];
			new_input[i_new + 2] = input[i_input];
			new_input[i_new + 3] = ' ';
			i_input++;
			i_new += 3;
		}
		else if ((input[i_input] == '|' && !check_closed_quotes(input, i_input))
			|| (input[i_input] == '>' && !check_closed_quotes(input, i_input))
			|| (input[i_input] == '<' && !check_closed_quotes(input, i_input)))
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

long long int	ft_atoll(const char *str)
{
	long long int			result;
	int						sign;

	result = 0;
	sign = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return ((long long int)result * sign);
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

bool	check_non_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i > 0)
		{
			if (!(str[i] >= '0' && str[i] <= '9'))
				return (true);
		}
		else
		{
			if (!(str[i] >= '0' && str[i] <= '9')
				&& str[i] != '-' && str[i] != '+')
				return (true);
		}
		i++;
	}
	return (false);
}

int	main(int ac, char **av, char **envp)
{
	t_data			*data;
	char			*input;
	int				temp_stdout;
	int				temp_stdin;
	long long int	num_exit;

	if (ac > 1 && av)
		error(ARGS, '\0');
	data = get_data(ac, av, envp);
	init_signal();
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while (1)
	{
		dup2(temp_stdout, STDOUT_FILENO);
		dup2(temp_stdin, STDIN_FILENO);
		input = get_input();
		cntr_d(input, &data);
		if (!input[0] || !check_input(input))
			free(input);
		else
		{
			add_history(input);
			input = new_input(input);
			data->tokens_head = get_tokens(data, input);
			if (!strncmp(data->tokens_head->command, "exit", 4))
			{
				if (len_data(data->tokens_head) > 2)
				{
					free_data(&data);
					write(2, "minishell: too many arguments\n", 31);
					exit(1);
				}
				else if (data->tokens_head->next)
				{
					if (check_non_numeric(data->tokens_head->next->command))
					{
						write(2, "minishell: numeric argument required\n", 38);
						free_data(&data);
						exit(2);
					}
					num_exit = ft_atoll(data->tokens_head->next->command);
					free_data(&data);
					exit((int)num_exit);
				}
				else
				{
					free_data(&data);
					exit(0);
				}
			}
			exec_tokens(data);
			unlink(TEMP_FILE);
			free_tokens(data);
		}
	}
	return (0);
}
