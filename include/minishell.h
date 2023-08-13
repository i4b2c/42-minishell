/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 22:30:48 by marvin            #+#    #+#             */
/*   Updated: 2023/08/11 22:30:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/src/libft.h"
//#include "../.pipex/pipex.h"

# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <strings.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdarg.h>
# include <stdint.h>
# include <inttypes.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/errno.h>
// #include <sys/kern_memorystatus.h>

#define MALLOC "minishell: Error Memory Allocation\n"
#define ARGS "Invalid argument: ./minishell\n"
#define INPUT "minishell: syntax error near unexpected token "
#define INPUT_NEW_LINE "minishell: syntax error near unexpected token `newline'\n"
#define SYNTAX_ENVP ""

typedef struct s_statlst
{
	int ac;
	char **av;
	struct s_statlst *next;
}	t_statlst;

typedef struct s_varlst
{
	char *var_name;
	char *var_value;
	struct s_varlst *next;
}	t_varlst;

typedef struct s_data
{
	char **envp;
	t_varlst *var_head;
	t_statlst *stat_head;
}	t_data;

void print_env(t_data *data);
int get_index_env(char *str);
void add_env(t_data *data,char *var);
bool check_input_env(char *var);

t_data *get_data(int ac, char **av, char **envp);
int ft_strlen(char *str);
void error(char *str, char *str_extra);

char *get_input(void);

void free_data(t_data **data);
void free_strings(char **str);

void exec(char *command);

void print_export(t_data *data);

void print_string(char **str);

void child_process(int sig);
void dimiss_signal(int sig);
void init_signal(void);

char *ft_mllstrcpy(char *str);
void add_list(t_data *data,t_varlst *temp_var);

#endif
