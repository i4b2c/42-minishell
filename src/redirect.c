#include "../include/minishell.h"

void change_stdout(char *str)
{
	int fd;

	fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd,STDOUT_FILENO);
}

void change_stdin(char *str)
{
	int fd;

	fd = open(str,O_RDONLY);
	dup2(fd,STDIN_FILENO);
}
