#include "../include/minishell.h"

void teste(int num)
{
	(void)num;
	write(1,"Nao acabou\n",11);
	return ;
}

/*
static void logic(char *str)
{
	(void)str;
    char *arg[] = {"tree", NULL};
    char cwd[256];
    getcwd(cwd, 256);
    //printf("teste:%s",cwd);
    char *executable = "tree";
    char *which = NULL;
    char *cmd = NULL;
    which = getenv("PATH");
    cmd = strtok(which, ":");
    while (cmd != NULL) {
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", cmd, executable);
        if (access(path, X_OK) == 0) {
            // o arquivo existe e é executável
			printf("\nteste%s e %s\n",path,cwd);
            execve(path, &arg[0], NULL);
        }
        cmd = strtok(NULL, ":");
    }
    // se chegamos até aqui, o arquivo "ls" não foi encontrado
    fprintf(stderr, "ls: comando não encontrado\n");
}*/

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
	(void)str;
	char *s1[] = {"ls",NULL};
	char path[256];
	char *comand;
	comand = calloc(256,1);
	easy_one(str);
	char *teste = getenv("PATH");
	char *outro_teste = strtok(teste,":");
	strcpy(path,outro_teste);
	strcpy(comand,"ls");
	int i = strlen(path);
	path[i] = '/';
	i++;
	int j = 0;
	while(comand[j])
	{
		path[i+j] = comand[j];
		j++;
	}
	free(comand);
	//tentar ver se tem o arquivo ls com o acess


	//(void)comand;
	path[i+j] = '\0';
	//while(outro_teste[i])
	//printf("%s",path);
	//char *arg[] = {"ls",NULL};
	execve(path,s1,NULL);
}

int main(void)
{
	char *str;
	while(1)
	{
		str = calloc(sizeof(1024),1);
		printf("\033[0;32mminishell$\033[0m");
		str = readline(" ");
		if(str[0])
		{
			add_history(str);
			logic(str);
		}
		free(str);
	}
}
