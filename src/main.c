#include "../include/minishell.h"

void teste(int num)
{
	(void)num;
	write(1,"Nao acabou\n",11);
	return ;
}

static void easy_one(char *str)
{
	char cwd[256];
	if(!(strcmp(str,"pwd")))
	{
		getcwd(cwd,256);
		printf("%s\n",cwd);
	}
	else if(!(strcmp(str,"exit")))
	{
		free(str);
		exit (0);
	}
}

static void logic(char *str)
{
	char *s1[2];
	char *path;
	char *comand;
	comand = calloc(256,1);
	char *teste;
	char *outro_teste;
	strcpy(comand,str);
	s1[0] = comand;
	s1[1] = NULL;
	int j = 0;
	int i = 0;
	int len = 0;
	char *cmd;
	teste = getenv("PATH");
	cmd = strtok(teste,":");
	while(cmd != NULL)
	{
		path = calloc(256,1);
		strcpy(path,cmd);
		path[ft_strlen(path)] = '/';
		ft_strlcat(path,comand,256);
		if(access(path,X_OK) == 0)
		{
			execve(path,s1,NULL);
			free(path);
			break;
		}
		cmd = strtok(NULL,":");
		free(path);
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
		str = ft_strtrim(str," ");
		add_history(str);
		if(str[0])
			logic(str);
		free(str);
	}
}
