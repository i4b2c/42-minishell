#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/src/libft.h"
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

# define MALLOC "minishell: Error Memory Allocation\n"
# define ARGS "Invalid argument: ./minishell\n"
# define INPUT "minishell: syntax error near unexpected token "
# define INPUT_NEW_LINE "minishell: unexpected token `newline'\n"
# define COMMAND_NOT_FOUND "minishell : command not found\n"
# define SYNTAX_ENVP ""

# define TEMP_FILE ".file_temp.txt"
# define TEMP_FILE_OUT ".file_out_temp.txt"

typedef enum e_type
{
	NORMAL,
	RDR_OUT,
	RDR_IN,
	RDR_AP_OUT,
	RDR_RD_IN,
	PIPE,
}	t_type;

typedef struct s_tokens
{
	int				fd_out;
	char			*command;
	t_type			type;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_statlst
{
	int					ac;
	char				**av;
	struct s_statlst	*next;
}				t_statlst;

typedef struct s_varlst
{
	char			*var_name;
	char			*var_value;
	struct s_varlst	*next;
}				t_varlst;

typedef struct s_data
{
	char		**envp;
	bool		check_out;
	bool		check_in;
	t_tokens	*tokens_head;
	t_varlst	*var_head;
	t_statlst	*stat_head;
}				t_data;

/*************\
|**--CHDIR--**|
\*************/
void		exec_chdir(char **i);

/************\
|**--DATA--**|
\************/
t_statlst	*get_stat(int ac, char **av);
t_varlst	*get_var(char **envp);
t_data		*get_data(int ac, char **av, char **envp);
char 		*get_path_input(char *input,t_data *data);
char		*get_path(char *input, int *i);
int			get_len_path(char *input, t_data *data);



/************\
|**--ECHO--**|
\************/
int			search_envp(t_data *data, char *cmd);
void		exec_echo(t_data *data, char **input);

/************\
|**--ENVP--**|
\************/
bool		check_exist_env(t_data *data, char *input);
void		change_exist_env(t_data *data, char **cmd);
bool		check_input_env(char *str);
void		change_env(t_data *data, char **input);

/*************\
|**--ERROR--**|
\*************/
int			error(char *str, char str_extra);

/************\
|**--EXEC--**|
\************/
char		*check_command(char *command, char **path);
char		*ft_getenv(const char *str, t_data *data);
void		ft_execve(char **command, t_data *data);
void		read_stdin(char *str, int fd);
int			pipe_string(t_tokens *token);
bool		try_simple_exec(char **command, t_data *data);
void		exec_tokens(t_data *data);

/**************\
|**--EXPORT--**|
\**************/
int			num_data_env(t_data *data);
char		*copy_var(t_varlst *temp);
char		**replicate_string(t_data *data);
void		sort_string(char **str);
void		print_export(t_data *data);

/************\
|**--FREE--**|
\************/
void		free_strings(char **str);
void		free_data(t_data **data);
void		free_tokens(t_data *data);

/*************\
|**--INPUT--**|
\*************/
char		*get_input(void);
bool		check_input(char *str);
int			get_next_quote(char *str, int begin, char quote);
bool		is_there_quotes(char *str);
char 		check_quote(char *str);
void		cntr_d(char *input, t_data **data);

/****************\
|**--REDIRECT--**|
\****************/
int			change_stdout(char *str, t_type type);
void		change_stdin(char *str);

/**************\
|**--SIGNAL--**|
\**************/
void		child_process(int sig);
void		dismiss_signal(int sig);
void		init_signal(void);

/**************\
|**--TOKENS--**|
\**************/
int			add_token(t_tokens **h, char *s, t_type t);
t_tokens	*tokens_input(char **i, t_data *d);
t_tokens	*get_tokens(t_data *data, char *str);

/*************\
|**--UNSET--**|
\*************/
void		exec_unset(t_data *data, char **input);

/*****************\
|**--UTIL ENVP--**|
\*****************/
void		print_env(t_data *data);

/*******************\
|**--UTIL STRING--**|
\*******************/
int			len_strings(char **cmd);
void		print_string(char **str);

/************\
|**--UTIL--**|
\************/
char		*ft_mllstrcpy(char *str);
void		add_list(t_data *data, t_varlst *temp);
int 	is_quote(char c);

#endif
