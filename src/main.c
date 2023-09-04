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

char *get_path_input(char *input,t_data *data) {
    int i = 0;
	int len = 0;
	char *temp_path;
	char *temp_input;

	len = get_len_path(input,data);
	temp_input = malloc(sizeof(char) * len);
	len = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[0] != '\'')
		{
			temp_path = get_path(input, &i);
			temp_path = ft_getenv(temp_path,data);
			int i_temp = 0;
			while(temp_path[i_temp])
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

char **split_input(char *input) {
	int input_len = strlen(input);
	char **tokens = (char **)malloc(sizeof(char *) * (input_len + 1));
	int token_count = 0;
	int i = 0;

	while (i < input_len)
	{
		while (i < input_len && input[i] == ' ')
			i++;

		if (i == input_len)
			break;
		int start = i;

		if (is_quote(input[i]))
		{
			char quote_type = input[i];
			i++;
			while (i < input_len && input[i] != quote_type)
				i++;
			tokens[token_count] = strndup(input + start, i - start + 1);
			token_count++;
			i++; // Avançar para o próximo caractere após a citação
			}
			else
			{
			while (i < input_len && input[i] != ' ' && !is_quote(input[i]))
				i++;
			tokens[token_count] = strndup(input + start, i - start);
			token_count++;
		}
	}

	tokens[token_count] = NULL; // Marcar o final da lista com NULL
	return tokens;
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
			// input = get_path_input(input,data);
			char **teste = split_input(input);
			//teste = get_path_input(teste,data);
			int i = 0;
			while(teste[i])
			{
				char *c_temp;
				teste[i] = get_path_input(teste[i],data);
				if(is_quote(teste[i][0]))
				{
					c_temp = malloc(2);
					c_temp[0] = teste[i][0];
					c_temp[1] = 0;
					teste[i] = ft_strtrim(teste[i],c_temp);
					free(c_temp);
				}
				i++;
				//printf("%s\n",teste[i++]);
			}
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
