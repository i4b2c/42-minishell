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
		else if(strncmp(input,"cd",2) == 0)
		{
			exec_chdir(input);
		}
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
