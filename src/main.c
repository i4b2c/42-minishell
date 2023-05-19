#include "../include/minishell.h"

static void easy_one(char *str)
{
	if(!(strcmp(str,"exit")))
	{
		free(str);
		exit (0);
	}
}

static void logic(char *str)
{
	char **s1;
	char *path;
	char *comand;
	pid_t pid;
	comand = calloc(256,1);
	char *teste;
	char *outro_teste;
	s1 = malloc(sizeof(char *) * 10);
	int temp_i = 0;
	char *teste_str;
	teste_str = strtok(str," ");
	while(teste_str != NULL)
	{
		s1[temp_i] = calloc(128,1);
		strcpy(s1[temp_i],teste_str);
		teste_str = strtok(NULL," ");
		temp_i++;
	}
	strcpy(comand,s1[0]);
	s1[temp_i] = calloc(1,1);
	s1[temp_i] = NULL;
	int j = 0;
	int i = 0;
	int len = 0;
	char *cmd;
	pid = fork();
	teste = getenv("PATH");
	outro_teste = strdup(teste);
	cmd = strtok(outro_teste,":");
	if(pid == -1)
	{
		write(2,"Error PID\n",10);
		free(comand);
		exit (0);
	}
	if(pid == 0)
	{
		while(cmd != NULL && *cmd != '\0')
		{
			path = calloc(256,1);
			strcpy(path,cmd);
			path[ft_strlen(path)] = '/';
			ft_strlcat(path,comand,256);
			if(access(path,X_OK) == 0)
			{
				execve(path,s1,NULL);//funcao para executar os comando , path = diretorio do arquivo binario
				//s1 = comando , **char por exemplo = {"ls","-l"}
				return ;
			}
			cmd = strtok(NULL,":");
			free(path);
		}
	}

	else
	{
		int status;
		waitpid(pid,&status,0);
	}
}

void handler(int sig)
{
	if(sig == SIGINT)
	{
		printf("\n");
		printf("\033[0;32mminishell$\033[0m ");
		return ;
	}

}

int main(void)
{
	char *str;
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask,SIGINT);
	sa.sa_flags = 0;
	if(sigaction(SIGINT,&sa,NULL) == -1)
		write(ERROR,"Error\n",6);
	while(1)
	{
		str = calloc(sizeof(1024),1);
		printf("\033[0;32mminishell$\033[0m");
		str = readline(" ");
		str = ft_strtrim(str,"\n");
		add_history(str);//comando usado para adicionar ao history
		easy_one(str);
		if(str[0] != '\0')
			logic(str);
		free(str);
	}
}
