#ifndef MINISHELL_H
#define MINISHELL_H

#define OUTPUT 1
#define ERROR 2

#include "../libft/src/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

typedef struct t_cmd
{
	char *cmd;
	struct t_cmd *next;
}	d_cmd;

void init();

#endif
