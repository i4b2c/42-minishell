#include "../include/minishell.h"

int change_stdout(char *str, t_type type)
{
	int	fd;

	if (type == RDR_OUT)
	{
		unlink(str);
		fd = open(str, O_WRONLY | O_CREAT , 0666);
	}
	else if(type == RDR_AP_OUT)
		fd = open(str, O_WRONLY | O_CREAT , 0666 | O_APPEND);
	dup2(fd,STDOUT_FILENO);
	return fd;
}

void change_stdin(char *str)
{
	int fd;

	fd = open(str,O_RDONLY);
	dup2(fd,STDIN_FILENO);
}
