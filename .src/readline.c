#include "../include/header.h"

int check_option(char *str, int i)
{
	while(str[i] == ' ' && str[i])
		i++;
	if(str[i] == '-')
		return 0;
	return 1;
}

void	dismiss_signal(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		//g_exit_status = 130;
	}
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
	char *first_cmd;

	i = 0;
	i = get_index_first_command(str);
	first_cmd = malloc(i+1);
	first_cmd = NULL;
	//depois verificar o motivo de eu nao conseguir copiar para o first_cmd
	ft_strlcpy(first_cmd,str,i);
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
	if (sig == SIGINT && pid > 0)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		//ft_putchar_fd('k', STDOUT_FILENO);

		//g_exit_status = 130;
		kill(pid,SIGKILL);
		//exit(130);
	}
	// if(sig == SIGINT)// && pid > 0)
	// {
	// 	ft_putchar_fd('\n', STDOUT_FILENO);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// 	exit(0);
	// 	//kill(pid, SIGKILL);
	// }
	// else if(sig == SIGINT && pid == -1)
	// {
	// 	ft_putchar_fd('\n', STDOUT_FILENO);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }

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

int get_len_input(char *input)
{
	char **input_split;
	int i;

	i = 0;
	input_split = ft_split(input,' ');
	while(input_split[i])
		i++;
	return i;
}

// void add_export(char *input ,char ***envp)
// {
// 	char **new_envp;
// 	char **temp_input;
// 	char **temp_envp;
// 	int i;
// 	int j;
// 	int len_cmd;

// 	i = 0;
// 	j = 0;
// 	temp_envp = *envp;
// 	while (temp_envp[i] != NULL)
// 		i++;

// 	len_cmd = get_len_input(input);
// 	temp_input = ft_split(input,' ');
// 	new_envp = malloc((i + len_cmd) * sizeof(char *));
// 	i = 0;
// 	while(j < i)
// 	{
// 		new_envp = malloc(strlen(temp_envp[j]) * sizeof(char));
// 		strcpy(new_envp[j],temp_envp[j]);
// 		j++;
// 	}
// 	new_envp[j] = temp_input[1];
// 	new_envp[++j] = NULL;
// 	envp = &new_envp;
// 	//return ;
// }

void add_export(char *input, char ***envp)
{
    char **new_envp;
    char **temp_input;
    char **temp_envp;
    int i;
    int j;
    int len_cmd;

    i = 0;
    j = 0;
    temp_envp = *envp;
    while (temp_envp[i] != NULL)
        i++;

    len_cmd = get_len_input(input);
    temp_input = ft_split(input,' ');
    new_envp = malloc((i + len_cmd + 1) * sizeof(char *));
    if (!new_envp)
    {
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }

    // Copy existing environment variables to new_envp
    while (j < i)
    {
        new_envp[j] = malloc(strlen(temp_envp[j]) + 1);
        if (!new_envp[j])
        {
            perror("Erro ao alocar memoria");
            exit(EXIT_FAILURE);
        }
        strcpy(new_envp[j], temp_envp[j]);
        j++;
    }

    // Add the new environment variable
    new_envp[j] = malloc(strlen(temp_input[1]) + 1);
    if (!new_envp[j])
    {
        perror("Erro ao alocar memoria");
        exit(EXIT_FAILURE);
    }
    strcpy(new_envp[j], temp_input[1]);
    new_envp[++j] = NULL;

    // Update the envp pointer
    *envp = new_envp;
}


void exec_export(char *input, char **envp)
{
	//(void)input;
    char **new_envp;
    int i = 0;
	int check;
	int j;

	check = 0;

	if(input[6])
	{
		add_export(input,& 	envp);
		return ;
	}
	while (envp[i] != NULL)
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));

	if (new_envp == NULL)
	{
		perror("Erro ao alocar memoria");
		exit(EXIT_FAILURE);
	}

	j = 0;
	while(j < i)
	{
		new_envp[j] = malloc(strlen(envp[j]) + 1);
		if (new_envp[j] == NULL)
		{
			perror("Erro ao alocar memoria");
			exit(EXIT_FAILURE);
		}
		strcpy(new_envp[j], envp[j]);
		j++;
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
	while (new_envp[i] != NULL)
	{
		//if(check == 1)
		//	ft_printf("declare -x ");
		printf("%s\n", new_envp[i]);
		i++;
	}

    // free memory

    // for (int j = 0; j < i; j++) {
	j = 0;
	while(j < i)
		free(new_envp[j++]);
	free(new_envp);
}

//extern char **__environ;

int main(int ac, char **av, char **envp)
{
	char *input;
	(void)ac;
	(void)av;
	struct sigaction	sa;

	sa.sa_handler = &dismiss_signal;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
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
			signal(SIGINT, handler);
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

