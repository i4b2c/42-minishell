/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:52:28 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/08 08:29:12 by marvin           ###   ########.fr       */
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

bool check_closed_quotes(const char *input, int i_str) {
    bool inside_quotes = false;
    char current_quote = '\0'; // Pode ser '' (aspas simples) ou '"' (aspas duplas)

    for (int i = 0; i < i_str; i++) {
        if (!inside_quotes && (input[i] == '\'' || input[i] == '"')) {
            inside_quotes = true;
            current_quote = input[i];
        } else if (inside_quotes && input[i] == current_quote) {
            inside_quotes = false;
        }
    }

    return inside_quotes;
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
		if (input[i_input] == '|' && !check_closed_quotes(input,i_input))
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
	//printf("new input ->%s\n", new_input);
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

// char	*get_path_input(char *input, t_data *data)
// {
//     int		i;
// 	int		len;
// 	int		i_temp;
// 	char	*temp_path;
// 	char	*temp_input;

// 	i = 0;
// 	len = get_len_path(input, data);
// 	temp_input = malloc(sizeof(char) * len);
// 	len = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '$' && input[0] != '\'')
// 		{
// 			temp_path = get_path(input, &i);
// 			temp_path = ft_getenv(temp_path, data);
// 			i_temp = 0;
// 			while (temp_path[i_temp])
// 			{
// 				temp_input[len] = temp_path[i_temp];
// 				i_temp++;
// 				len++;
// 			}
// 			free(temp_path);
// 		}
// 		else
// 		{
// 			temp_input[len] = input[i];
// 			len++;
// 			i++;
// 		}
// 	}
// 	temp_input[len] = 0;
// 	return (temp_input);
// }

char	**cut_quote(char **tokens, t_data *data)
{
	int		i;
	char	*c_temp;

	i = 0;
	//printf("%s\n", tokens[0]);
	while (tokens[i])
	{
		//printf("%s\n", tokens[0]);
		tokens[i] = get_path_input(tokens[i],data);
		printf("%s\n", tokens[i]);    //ANTES DO STRTRIM<--aqui eu vou ver o head->command ou todos os tokens.
		if (is_quote(tokens[i][0]))
		{
			c_temp = malloc(2);
			c_temp[0] = tokens[i][0];
			c_temp[1] = 0; /*<-- BUG = aqui ele vai dar strtrim das quotes, mas como o token[0]
				é = "" ele vai dar trim aos "" e vai ficar vazio, dai quando dou printf do
				token[0] antes de entrar aqui ele mostra me o "", quando dou printf do token[0]
				no final, já me dá '\0' porque já fez o trim.*/
			tokens[i] = ft_strtrim(tokens[i], c_temp);
			free(c_temp);
		}
		i++;
	}
	//printf("%s\n", tokens[0]);
	/*DEPOIS DO STRTRIM<-- aqui eu printo o token[0] supostamente neste caso teria de ser o echo
			mas não é. quando se põe mais de um par de quotes dá BUG. BUG explicado em cima.*/
	//printf("%s\n", tokens[2]);
	//printf("%s\n", tokens[3]);
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
			quote_type = input[i];/*quando pomos mais de um par de quotes, o input[i]
									vai ser igual a '"', depois do i++, o input[i]
									vai ser igual a '"' na mesma, porque o input leva
									dois pares ou mais de quotes! neste caso é ""echo""*/
			i++;
			while (i < input_len && input[i] != quote_type)/*aqui o input[i], como já vimos em cima
															vai ser igual a '"', sendo assim igual ao quote_type
															e já não satisfaz a condição input[i] != quote_type,
															logo o tokens[tokens_count] depois vai ser igual
															a "" em vez de ser igual a ""echo""*/
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
	//printf("%s\n", tokens[0]);
	tokens[token_count] = NULL;
	return (cut_quote(tokens,data));
}

//apenas para teste
void print_tokens(t_data *data)
{
	t_tokens *temp = data->tokens_head;
	while(temp)
	{
		printf("%s -> %d\n",temp->command,temp->type);
		temp = temp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	char	*input;
	int		temp_stdout;
	int		temp_stdin;
	//char	**input_split;

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
			//input_split = split_input(input, data);
			data->tokens_head = get_tokens(data, input);
			// print_tokens(data);
			//printf("first token ->%s\n", data->tokens_head->command); //-- confirma que o primeiro comando está com bug
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
