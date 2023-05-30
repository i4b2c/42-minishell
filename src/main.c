#include "../include/minishell.h"

static int contar_string(char **str)
{
	int i;

	i = 0;
	while(str[i] != NULL)
		i++;
	return i;
}

static int cd_dir(char *str)
{
	char *dir;
	char *cwd;
	char **av;
	static char *oldPwd;
	int len;

	if(!oldPwd)
		oldPwd = calloc(1024,1);
	av = ft_split(str,' ');
	if(!strcmp(av[0],"cd"))
	{
		dir = calloc(1024,1);
		cwd = calloc(1024,1);
		getcwd(cwd,1024);
		strcpy(dir,cwd);
		if(contar_string(av) > 2)
		{
			write(2,"-bash: ",7);
			write(2,"too many arguments\n",19);
			return 1;
		}
		if(av[1][0] == '"' && av[1][strlen(av[1])-1] == '"')//avancar caso esteja cd ".." , assim ja funciona sem problema
		{
			av[1]++;
			av[1][strlen(av[1])-1] = 0;
		}
		if(!strcmp(av[1],".."))
		{
			strcpy(oldPwd,dir);
			len = strlen(dir) - 1;
			while(dir[len] != '/')
			{
				if(len != 0)
					dir[len] = 0;
				len--;
			}
			if(len != 0)
				dir[len] = 0;
		}
		else if(!strcmp(av[1],"-"))
		{
			printf("%s\n",oldPwd);
			strcpy(dir,oldPwd);
		}
		else
		{
			strcat(dir,"/");
			strcat(dir,av[1]);
		}
		chdir(dir);
		free(cwd);
		free(dir);
		return 1;
	}
	return 0;
}

static void easy_one(char *str)
{
	if(!(strcmp(str,"exit")))
	{
		free(str);
		kill(0,SIGTERM);//acabar com os processos filhos
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


	//criar uma logica para executar binarios propios , so usar execve no pwd , que eu ACHO que da certo
	easy_one(str);
	pid = fork();
	teste = getenv("PATH");
	outro_teste = strdup(teste);
	//tem que criar um duplicado porque quando usamos strtok ele avanca na memoria
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
		if(cmd == NULL)
			write(2,"command not found\n",18);
		return ;
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
	else if(sig == SIGTERM)
		exit(0);
}

int main(void)
{
	char *str;
	struct sigaction sa;
	int num;
	//t_pid pid;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask,SIGINT);
	sigaddset(&sa.sa_mask,SIGTERM);
	//sigaddset(&sa.sa_mask,SIG);
	sa.sa_flags = 0;
	if(sigaction(SIGINT,&sa,NULL) == -1)
		write(ERROR,"Error\n",6);
	if(sigaction(SIGTERM,&sa,NULL) == -1)
		write(ERROR,"Error\n",6);
	while(1)
	{
		num = 0;
		str = calloc(sizeof(1024),1);
		printf("\033[0;32mminishell$\033[0m");
		str = readline(" ");
		str = ft_strtrim(str,"\n");
		if(str[0] != '\0')
		{
			add_history(str);//comando usado para adicionar ao history
			//easy_one(str,pid);
			num = cd_dir(str);
			if(num == 0)
				logic(str);
		}
		free(str);
	}
}
