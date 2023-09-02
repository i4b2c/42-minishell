#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

int get_len_pipes(char *input)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while(input[i])
	{
		if(input[i] == '|')
			len++;
		i++;
	}
	return (len);
}

char *new_input(char *input)
{
	int i_input;
	int i_new;
	char *new_input;

	i_input = 0;
	i_new = 0;
	new_input = malloc(((get_len_pipes(input) * 2) + 1 + ft_strlen(input)) * sizeof(char));
	while(input[i_input])
	{
		if(input[i_input] == '|')
		{
			new_input[i_new] = ' ';
			new_input[i_new+1] = input[i_input];
			new_input[i_new+2] = ' ';
			i_new += 2;
		}
		else
			new_input[i_new] = input[i_input];
		i_new++;
		i_input++;
	}
	new_input[i_new] = 0;
	free(input);
	return new_input;
}

char *ft_mllstrcat(char *str1, char *str2,char c)
{
	char *temp;
	int i1;
	int i2;

	if(!str1)
		return(ft_mllstrcpy(str2));
	if(!c)
		temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	else
		temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
	i1 = -1;
	while(str1[++i1])
		temp[i1] = str1[i1];
	if(c)
		temp[i1++] = c;
	i2 = -1;
	while(str2[++i2])
		temp[i1 + i2] = str2[i2];
	temp[i1 + i2] = 0;
	return (temp);
}

int check_quotes_input(char *str)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while(str[i])
	{
		if(str[i] == '"')
			len++;
		i++;
	}
	return len;
}

// char **split_input(char *input) {
//     char **temp = ft_split(input, ' ');
//     char **new_input = malloc((sizeof(char *)) * (strlen(input) + 1)); // Alocação corrigida
//     int j = 0;
//     int inside_quotes = 0;
//     char *current_word = NULL;

//     for (int i = 0; temp[i]; i++) {
//         if (check_quotes_input(temp[i]) % 2 != 0) {
//             if (!inside_quotes) {
//                 current_word = ft_mllstrcpy(temp[i]);
//                 inside_quotes = 1;
//             } else {
//                 current_word = ft_mllstrcat(current_word, temp[i], ' ');
//                 new_input[j++] = current_word;
//                 inside_quotes = 0;
//                 current_word = NULL;
//             }
//         } else if (inside_quotes) {
//             current_word = ft_mllstrcat(current_word, temp[i], ' ');
//         } else {
//             new_input[j++] = ft_mllstrcpy(temp[i]);
//         }
//     }

//     new_input[j] = NULL;
//     // Libere a memória alocada para temp e current_word
//     // ...

//     return new_input;
// }

// int is_quote(char c) {
//     return (c == '"' || c == '\'');
// }
// char **split_input(char *input) {
// 	char **temp = ft_split(input, ' ');
//     char **new_input = malloc(sizeof(char *) * (sizeof(temp) + 1));
//     int j = 0;
//     char *current_word = NULL;
//     char char_temp = '\0';

//     for (int i = 0; temp[i]; i++) {
//         if (temp[i][0] == '\'' || temp[i][0] == '"') {
//             if (current_word == NULL) {
//                 char_temp = temp[i][0];
//                 current_word = ft_mllstrcpy(temp[i]);
//             } else {
//                 current_word = ft_mllstrcat(current_word, " ", 0);
//                 current_word = ft_mllstrcat(current_word, temp[i], 0);

//                 if (temp[i][strlen(temp[i]) - 1] == char_temp) {
//                     new_input[j++] = current_word;
//                     current_word = NULL;
//                     char_temp = '\0';
//                 }
//             }
//         } else if (current_word != NULL) {
//             current_word = ft_mllstrcat(current_word, " ", 0);
//             current_word = ft_mllstrcat(current_word, temp[i], 0);

//             if (temp[i][strlen(temp[i]) - 1] == char_temp) {
//                 new_input[j++] = current_word;
//                 current_word = NULL;
//                 char_temp = '\0';
//             }
//         } else {
//             new_input[j++] = ft_mllstrcpy(temp[i]);
//         }
//     }
//     new_input[j] = NULL;
//     free_strings(temp);

//     return new_input;
// }


char **split_input(char *input) {
//     char **temp = ft_split(input, ' ');
//     char **new_input = malloc(sizeof(char *) * (sizeof(temp) + 1));
//     int j = 0;
//     char *current_word = NULL;
//     char char_temp = '\0';

//     for (int i = 0; temp[i]; i++) {
//         if (is_quote(temp[i][0])) {
//             if (current_word == NULL) {
//                 char_temp = temp[i][0];
//                 current_word = ft_mllstrcpy(temp[i]);
//                 if (strlen(temp[i]) == 1 || temp[i][strlen(temp[i]) - 1] == char_temp) {
//                     new_input[j++] = current_word;
//                     current_word = NULL;
//                     char_temp = '\0';
//                 }
//             } else {
//                 current_word = ft_mllstrcat(current_word, " ", 0);
//                 current_word = ft_mllstrcat(current_word, temp[i], 0);

//                 if (temp[i][strlen(temp[i]) - 1] == char_temp) {
//                     new_input[j++] = current_word;
//                     current_word = NULL;
//                     char_temp = '\0';
//                 }
//             }
//         } else if (current_word != NULL) {
//             current_word = ft_mllstrcat(current_word, " ", 0);
//             current_word = ft_mllstrcat(current_word, temp[i], 0);

//             if (temp[i][strlen(temp[i]) - 1] == char_temp) {
//                 new_input[j++] = current_word;
//                 current_word = NULL;
//                 char_temp = '\0';
//             }
//         } else {
//             new_input[j++] = ft_mllstrcpy(temp[i]);
//         }
//     }
//     new_input[j] = NULL;
//     free_strings(temp);

//     return new_input;
// }
    char **temp = ft_split(input, ' ');
    char **new_input = malloc(sizeof(char *) * (sizeof(temp) + 1));
    int j = 0;
    char *current_word = NULL;

    for (int i = 0; temp[i]; i++) {
        char *token = temp[i];
        while (token) {
            // Verifique se o token começa com aspas simples, aspas duplas ou chaves
            if (token[0] == '\'' || token[0] == '"' || token[0] == '{') {
                char delimiter = (token[0] == '{') ? '}' : token[0];
                int len = strlen(token);
                current_word = ft_mllstrcpy(token + 1); // Ignorar o caractere de abertura
                if (token[len - 1] == delimiter) {
                    // A palavra está completamente contida nas aspas ou chaves
                    current_word[len - 2] = '\0'; // Remova o caractere de fechamento
                    new_input[j++] = current_word;
                    current_word = NULL;
                } else {
                    // Prossiga para o próximo token
                    token = strchr(token + 1, delimiter);
                    if (token) {
                        current_word = ft_mllstrcat(current_word, " ", ' ');
                        current_word = ft_mllstrcat(current_word, token + 1, ' ');
                        if (token[strlen(token) - 1] == delimiter) {
                            token = NULL;
                        }
                    }
                }
            } else if (strchr(token, '|') || strchr(token, '<') || strchr(token, '>')) {
                // Manipule operadores de redirecionamento e pipes como palavras separadas
                new_input[j++] = ft_mllstrcpy(token);
                token = NULL;
            } else {
                new_input[j++] = ft_mllstrcpy(token);
                token = NULL;
            }
        }
    }
    new_input[j] = NULL;
    free_strings(temp);

    return new_input;
}

// char *get_path(char *input, int *i)
// {
// 	(*i)++;
// 	int i_temp = *i;
// 	while(input[i_temp] && ft_isalnum(input[i_temp]))
// 		i_temp++;
// 	char *temp = malloc(sizeof(char) * ((*i) - i_temp + 1));
// 	int len = 0;
// 	while(input[*i] && ft_isalnum(input[*i]))
// 	{
// 		temp[len] = input[*i];
// 		(*i)++;
// 		len++;
// 	}
// 	temp[len] = 0;
// 	return temp;
// }

// char *get_path_input(char *input, t_data *data)
// {
// 	int i;

// 	i = 0;
// 	(void)data;
// 	while(input[i])
// 	{
// 		if(input[i] == '$')
// 		{
// 			char *temp_path;

// 			temp_path = get_path(input,&i);
// 			printf("%s\n",temp_path);
// 			free(temp_path);
// 		}
// 		else
// 			i++;
// 	}
// 	return input;
// }

char *get_path(char *input, int *i) {
    (*i)++;
    int i_temp = *i;
    while (input[i_temp] && isalnum(input[i_temp]))
        i_temp++;
    char *temp = malloc(sizeof(char) * (i_temp - *i + 1));
    int len = 0;
    while (input[*i] && isalnum(input[*i])) {
        temp[len] = input[*i];
        (*i)++;
        len++;
    }
    temp[len] = '\0';
    return temp;
}

int get_len_path(char *input, t_data *data)
{
	int len = 0;
	int i = 0;
	while (input[i]) {
        if (input[i] == '$') {
            char *temp_path = get_path(input, &i);
			temp_path = ft_getenv(temp_path,data);
			len += ft_strlen(temp_path);
            free(temp_path);
        } else {
			len++;
            i++;
        }
    }
	return (len + 1);
}

bool check_quotes(char *input, int len)
{
	int i;
	int i_quote;
	int i_double_quotes;
	int len_quote;
	int len_double_quotes;

	i = 0;
	i_quote = 0;
	i_double_quotes = 0;
	len_quote = 0;
	len_double_quotes = 0;
	while(input[i] && i < len)
	{
		if(input[i] == '\'')
		{
			i_quote = i;
			len_quote++;
		}
		if(input[i] == '"')
		{
			i_double_quotes = i;
			len_double_quotes++;
		}
		i++;
	}
	if(len_quote % 2)
		return false;
	return true;
}

char *get_path_input(char *input,t_data *data) {
    int i = 0;
	int len = 0;

	len = get_len_path(input,data);
	char *temp_input = malloc(sizeof(char) * len);
	len = 0;
    while (input[i]) {
        if (input[i] == '$' && check_quotes(input,i)) {
            char *temp_path = get_path(input, &i);
			temp_path = ft_getenv(temp_path,data);
			int i_temp = 0;
			while(temp_path[i_temp])
			{
				temp_input[len] = temp_path[i_temp];
				i_temp++;
				len++;
			}
            free(temp_path);
        } else {
			temp_input[len] = input[i];
			len++;
            i++;
        }
    }
	temp_input[len] = 0;
    return temp_input;
}

int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;
	int temp_stdout;
	int temp_stdin;

	if(ac > 1 && av)
		error(ARGS,NULL);
	data = get_data(ac,av,envp);
	init_signal();
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while(1)
	{
		//reset();
		dup2(temp_stdout,STDOUT_FILENO);
		dup2(temp_stdin,STDIN_FILENO);
		input = get_input();
		if(!input[0])
			free(input);
		else
		{
			add_history(input);
			input = new_input(input);
			input = get_path_input(input,data);
			// free(input);
			// input = ft_mllstrcpy("echo '$PATH' 'ok' teste");
			// printf("%s\n",input);
			data->tokens_head = tokens_input(input,data);
			if(!strncmp(data->tokens_head->command,"exit",4))
			{
				free_data(&data);
				break;
			}
			exec_tokens(data);
			unlink(TEMP_FILE);
			free_tokens(data);
		}
	}
	return 0;
}
