/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:16:58 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/08 08:11:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern volatile long long g_exit_status;

int	get_unquoted_size(char *str)
{
	int	start;
	int	i;

	i = 0;
	if (str[i] == '"')
	{
		while (str[i] == '"')
			i++;
		start = i;
		while (str[i] != '"')
			i++;
		return (i - start);
	}
	else if (str[i] == '\'')
	{
		while (str[i] == '\'')
			i++;
		start = i;
		while (str[i] != '\'')
			i++;
		return (i - start);
	}
}

char	*remove_single_quotes(char *str)
{
	int i;
	int j;
	char * quotes_free;

	i = 0;
	j = 0;
	int size = get_unquoted_size(str);
	//printf("%d\n", size);
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

//removes all the double quotes from the input(str)
//returns the quote_free str malloced

char	*remove_double_quotes(char *str)
{
	int i;
	int j;
	char *quotes_free;

	i = 0;
	j = 0;
	int size = get_unquoted_size(str);
	//printf("%d\n", size);
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

t_type	is_there_token(char c)
{
	if (c == '<')
		return (RDR_IN);
	if (c == '>')
		return (RDR_OUT);
	if (c == '|')
		return (PIPE);
	return (NORMAL);
}
/*
void	add_token(t_tokens **head, char *str, t_type type)
{
	t_tokens	*new_token;
	t_tokens	*temp;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->command = ft_mllstrcpy(str);
	new_token->type = type;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	printf("tokens ->%s\n", new_token->command);
}
*/

int add_token(t_tokens **head, char *str,t_type type)
{
    t_tokens *new_token;
	t_tokens *temp;

	new_token = malloc(sizeof(t_tokens));
    if (!new_token)
        return (-1);
    new_token->command = ft_strdup(str); //tambem dá com ft_strdup
	new_token->type = type;
    new_token->next = NULL;
    if (!*head)
        *head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	//printf("token ->%s\n", new_token->command);
	return (0);
}
//RDR_RD_IN
int	get_new_token(char *str, int i, t_tokens **head)
{
	int checker;

	if (str[i] == '<' && str[i + 1] == '<')
	{
		checker = add_token(head, NULL, RDR_RD_IN);
		i += 1;
	}
	else if (str[i] == '>' && str[i + 1] == '>')
	{
		checker = add_token(head, NULL, RDR_AP_OUT);
		i += 1;
	}
	else if (str[i] == '<')
		checker = add_token(head, NULL, RDR_IN);
	else if (str[i] == '>')
		checker = add_token(head, NULL, RDR_OUT);
	else if (str[i] == '|')
		checker = add_token(head, NULL, PIPE);
	if (checker == (-1))
		return (checker);
	return (i);
}

int	get_word_until(char *str, int i, t_tokens **head)
{
	int	begin;
	int	checker;

	begin = i;
	while (str[i])
	{
		if (is_there_token(str[i] != NORMAL) || str[i] == ' ' || str[i] == '\t')
			break ;
		if (str[i] == '\'')
			i = get_next_quote(str, i, '\'');
		else if (str[i] == '"')
			i = get_next_quote(str, i, '"');
		i++;
	}
	checker = add_token(head, ft_substr(str, begin, i - begin), NORMAL);
	if (checker == (-1))
		return (checker);
	return (i);
}

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
		if(input[i] == '$' && input[i+1] == '?'
			&& input[0] != '\'')
			{
				char *temp_int;
				int i_int_temp = 0;

				temp_int = ft_itoa(g_exit_status);
				while(temp_int[i_int_temp])
				{
					temp_input[len] = temp_int[i_int_temp];
					i_int_temp++;
					len++;
				}
				i += 2;
				free(temp_int);
			}
		else if(input[i] == '$' && !ft_isalnum(input[i+1]))
		{
			temp_input[len++] = '$';
			i++;
		}
		else if (input[i] == '$' && input[0] != '\'')
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


void	remove_head_quotes(t_tokens *head,t_data *data)
{
	//int	i;

	//i = 0;
	if (is_there_quotes(head->command))
	{
		if (head->command[0] == '\'')
			head->command = remove_single_quotes(head->command);
		else if (head->command[0] == '"')
		{
			head->command = get_path_input(head->command,data);
			head->command = remove_double_quotes(head->command);
		}
	}
	else
		return ;
}

char check_quote(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\'' || str[i] == '"')
			break;
		i++;
	}
	return str[i];
}

void	remove_quotes(t_tokens *head,t_data *data)
{
	char c_temp;
	while (head != NULL)
	{
		c_temp = check_quote(head->command);
		if(c_temp != '\'')
			head->command = get_path_input(head->command,data);
		if(c_temp == '\'')
			head->command = remove_single_quotes(head->command);
		else if(c_temp == '"')
			head->command = remove_double_quotes(head->command);
		head = head->next;
	}
}

t_tokens	*get_tokens(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while(str[i] == ' ' || str[i] == '\t')
			i++;
		if (is_there_token(str[i]) != NORMAL)
			i = get_new_token(str, i, &data->tokens_head);
		else
			i = get_word_until(str, i, &data->tokens_head);
		if (i < 0)
			return (NULL);
		else if (str[i] == '\0')
			break ;
		//remove_head_quotes(data->tokens_head); //remove the quotes only from the first token(command)
		i++;
	}
	remove_quotes(data->tokens_head,data); //remove the quotes from all the tokens(commands)
	return (data->tokens_head);
}



/*
void	add_token(t_tokens **head, char *str, t_type type)
{
	t_tokens	*new_token;
	t_tokens	*temp;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return ;
	new_token->command = ft_mllstrcpy(str);
	new_token->type = type;
	new_token->next = NULL;
	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
	printf("tokens ->%s\n", new_token->command);
}

t_tokens	*tokens_input(char **command, t_data *data)
{
	t_tokens	*temp;
	t_type		type;
	char		**split_pipe;
	int			i;

	i = 0;
	temp = NULL;
	type = NORMAL;
	while (command[i])
	{
		if (!ft_strchr(command[i], '>')
			&& !ft_strchr(command[i], '<'))
		{
			if (ft_strchr(command[i], '|'))
			{
				add_token(&temp, "|", PIPE);
				type = NORMAL;
			}
			else
				add_token(&temp, command[i], type);
			type = NORMAL;
			i++;
		}
		else
		{
			if (!ft_strncmp(command[i], ">>", 3))
				type = RDR_AP_OUT;
			else if (!ft_strncmp(command[i], "<<", 3))
				type = RDR_RD_IN;
			else if (ft_strchr(command[i], '>'))
				type = RDR_OUT;
			else if (ft_strchr(command[i], '<'))
				type = RDR_IN;
			i++;
		}
	}
	free_strings(command);
	return (temp);
}
*/

