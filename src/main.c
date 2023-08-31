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
    char **temp = ft_split(input, ' ');
    char **new_input = malloc(sizeof(char *) * (sizeof(temp) + 1));
    int j = 0;
    char *current_word = NULL;
    char char_temp = '\0';

    for (int i = 0; temp[i]; i++) {
        if (is_quote(temp[i][0])) {
            if (current_word == NULL) {
                char_temp = temp[i][0];
                current_word = ft_mllstrcpy(temp[i]);
                if (strlen(temp[i]) == 1 || temp[i][strlen(temp[i]) - 1] == char_temp) {
                    new_input[j++] = current_word;
                    current_word = NULL;
                    char_temp = '\0';
                }
            } else {
                current_word = ft_mllstrcat(current_word, " ", 0);
                current_word = ft_mllstrcat(current_word, temp[i], 0);

                if (temp[i][strlen(temp[i]) - 1] == char_temp) {
                    new_input[j++] = current_word;
                    current_word = NULL;
                    char_temp = '\0';
                }
            }
        } else if (current_word != NULL) {
            current_word = ft_mllstrcat(current_word, " ", 0);
            current_word = ft_mllstrcat(current_word, temp[i], 0);

            if (temp[i][strlen(temp[i]) - 1] == char_temp) {
                new_input[j++] = current_word;
                current_word = NULL;
                char_temp = '\0';
            }
        } else {
            new_input[j++] = ft_mllstrcpy(temp[i]);
        }
    }
    new_input[j] = NULL;
    free_strings(temp);

    return new_input;
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
			char **teste = split_input(input);
			data->tokens_head = tokens_input(teste,data);
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
