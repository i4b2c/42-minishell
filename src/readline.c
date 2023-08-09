#include "../include/header.h"

/*
nao consegui instalar por conta do windows
ou nao sei instalar , nao sei :)

funcoes para usar ->
readline
rl_clear_history
rl_on_new_line
rl_replca_line
rl_redisplay
add_history
*/

// void swap_strings(char **a, char **b) {
//     char *temp = *a;
//     *a = *b;
//     *b = temp;
// }

// int get_size(char **str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i] != NULL)
// 		i++;
// 	return i;
// }

// // Função para organizar um array de strings em ordem crescente
// char **organize_strings(char **str) {
// 	int count;
// 	int i = 0;
// 	char **temp;

// 	count = get_size(str);
// 	printf("%d\n",count);
// 	temp = malloc(sizeof(char **));
// 	while(i <= count)
// 	{
// 		printf("%s\n",str[i]);
// 		i++;
// 		//temp[i] = malloc(ft_strlen(str[i]) * sizeof(char));
// 		//ft_strcpy(temp[i],str[i]);
// 		//i++;
// 	}
// 	temp[i] = NULL;
//     // for (int i = 0; i < count - 1; i++) {
//     //     for (int j = 0; j < count - i - 1; j++) {
//     //         if (strcmp(temp[j], temp[j + 1]) > 0) {
//     //             swap_strings(&temp[j], &temp[j + 1]);
//     //         }
//     //     }
//     // }
// 	return NULL;
// 	// return temp;
// }

int check_option(char *str, int i)
{
	while(str[i] == ' ' && str[i])
		i++;
	if(str[i] == '-')
		return 0;
	return 1;
}

int get_index_first_command(char *str)
{
	int check;
	int i;

	i = 0;
	check = 0;
	while(str[i] != 0 && str[i] != '|')
	{
		if(str[i] == ' ')
			check = check_option(str,i);
		if(check == 1)
			break;
		i++;
	}
	return i;
}

void pipex_mult(char *str)
{
	int i;
	int j = 0;
	char *first_cmd;

	i = 0;
	i = get_index_first_command(str);
	first_cmd = malloc(i);
	first_cmd = NULL;
	//depois verificar o motivo de eu nao conseguir copiar para o first_cmd
	while(j < i)
	{
		first_cmd[j] = str[j];
		j++;
	}
	//ft_strlcpy(first_cmd,str,i);
	printf("%d %s\n",i,first_cmd);
	write(1,"ok\n",3);
}

int check_pipe(char *str)
{
	int i;

	i = 0;
	while(str[i] != 0)
	{
		if(str[i] == '|')
			return 1;
		i++;
	}
	return 0;
}

pid_t pid = -1;

void handler(int sig)
{
	if(sig == SIGINT && pid > 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		kill(pid, SIGKILL);
	}
}

void teste(int sig)
{
	ft_printf("ok %d\n",sig);
}

void exec_chdir(char *input)
{
	char **cmd;

	cmd = ft_split(input,' ');
	if(chdir(cmd[1]) != 0)
		perror("chdir ");
	free(cmd);
	return ;
}

//string vector cpy
// void ft_strvcpy(char **env,char **envp)
// {

// }

void organize_strings(char **new_envp) {
    char *temp;
    int i, j;

    i = 0;
    while (new_envp[i] != NULL) {
        j = i + 1; // Começa a verificação na próxima posição
        while (new_envp[j] != NULL) {
            if (ft_strncmp(new_envp[i], new_envp[j], ft_strlen(new_envp[j])) > 0) {
                temp = new_envp[i];
                new_envp[i] = new_envp[j];
                new_envp[j] = temp;
            }
            j++;
        }
        i++;
    }
}


void exec_export(char *input, char **envp)
{
	//(void)input;
    char **new_envp;
    int i = 0;
	int check;

	check = 0;
    while (envp[i] != NULL) {
        i++;
    }

    new_envp = malloc((i + 1) * sizeof(char *));

    if (new_envp == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    //copiar
    for (int j = 0; j < i; j++) {
        new_envp[j] = malloc(strlen(envp[j]) + 1);
        if (new_envp[j] == NULL) {
            perror("Erro ao alocar memória");
            exit(EXIT_FAILURE);
        }
        strcpy(new_envp[j], envp[j]);
    }

    new_envp[i] = NULL;
	if(strncmp(input,"export",6) == 0)
		check = 1;
	if(check == 1)
		organize_strings(new_envp);

	//imprimir para checkar
	//depois para imprimir certo o export posso imprimir ate o '='
	//depois imprimir '"'
	//acaba de imprimir ate o '\n' com o '\n' fora do output
	//imprimi '"' e um \n e ta feito
    i = 0;
    while (new_envp[i] != NULL) {
		if(check == 1)
			ft_printf("declare -x ");
        printf("%s\n", new_envp[i]);
        i++;
    }

    // free memory
    for (int j = 0; j < i; j++) {
        free(new_envp[j]);
    }
    free(new_envp);
}

//extern char **__environ;

int main(int ac, char **av, char **envp)
{
	char *input;
	(void)ac;
	(void)av;
	signal(SIGINT, handler);
	signal(SIGQUIT, teste);
	while((input = readline("\033[0;32mminishell $>\033[0m ")) != NULL)
	{
		add_history(input);
		if(strcmp(input,"exit") == 0)
		{
			free(input);
			break;
		}
		else if(strncmp(input,"export",6) == 0
			|| strncmp(input,"env",3) == 0)
			exec_export(input,envp);
		else if(strncmp(input,"cd",2) == 0)
			exec_chdir(input);
		else
		{
			pid = fork();
			if(pid == (pid_t) 0)
			{
				exec(input,envp);
				return 0;
			}
			else
				waitpid(pid,NULL,0);
			free(input);
		}
	}
	return 0;
}

