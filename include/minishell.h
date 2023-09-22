/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:30:07 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 14:30:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>

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

typedef struct s_varlst
{
	char			*var_name;
	char			*var_value;
	struct s_varlst	*next;
}				t_varlst;

typedef struct s_data
{
	int			fd_in;
	int			fd_out;
	char		*input;
	bool		check_pipe;
	char		**envp;
	bool		check_out;
	bool		check_in;
	t_tokens	*tokens_head;
	t_varlst	*var_head;
}				t_data;

bool			check_extra_chdir(char *str);
void			exec_chdir(char **input);

void			add_var_list(t_varlst **head, t_varlst *new, t_varlst **temp);
t_varlst		*get_var(char **envp);
t_data			*get_data(int ac, char **av, char **envp);

int				search_envp(t_data *data, char *cmd);
void			exec_echo(t_data *data, char **input);

bool			check_exist_env(t_data *data, char *input);
void			change_exist_env(t_data *data, char **command);
bool			check_input_env(char *str);
void			check_exist(t_data *data, char *input,
					char **command, t_varlst *temp_var);
void			change_env(t_data *data, char **input);
void			print_env(t_data *data);

int				error(char *str, char str_extra);

int				error_dir(char **command);
int				error_nf(char **command);
int				error_access(char **command);
void			ft_execve(char **command, t_data *data);
void			exec_command(char **command, t_data *data);
void			choose_exec(char **command, t_data *data);
char			**exec_pipe(t_data *data, char **command, int len, int i);
void			exec_tokens(t_data *data);

int				len_tokens(t_tokens *head);
bool			choose_redirect(int *i,
					char **command, t_tokens *temp, t_data *data);
void			last_fd(t_data *data);
int				is_quote(char c);
char			*cut_quotes(char *input, char quote);
int				pipe_string(t_tokens *tokens);
char			*check_command(char *command, char **path);
char			*ft_getenv(char *str, t_data *data, bool op);

void			check_exit(t_data *data);

int				num_data_env(t_data *data);
char			*copy_var(t_varlst *temp);
char			**replicate_string(t_data *data);
void			sort_string(char **str);
void			print_export(t_data *data);

void			free_strings(char **str);
void			free_data(t_data **data);
void			free_tokens(t_data *data);

char			*get_input(void);
char			*new_input(char *input);
bool			invalid_operator(char *str, int i);
bool			check_redirect(char *str, int i);
bool			check_quotes(char *str);
void			change_double_input(char *new_input,
					char *input, int *i_new, int *i_input);
void			change_simple_input(char *new_input,
					char *input, int *i_new, int i_input);
bool			check_input(char *str);

char			*get_path(char *input, int *i);
int				get_len_path(char *input, t_data *data);
void			path_echo_exit(char *temp_input, int *len, int *i);
void			path_echo(t_data *data, char *temp_input, int *i, int *len);
char			*get_path_input(char *input, t_data *data);

int				change_stdout(char *str, t_type type);
bool			change_stdin(char *str);
void			execute_rdin(int fd, char *str);
void			read_stdin(char *str, int fd_temp);

void			child_process(int signum);
void			dismiss_signal(int signum);
void			init_signal(void);
void			cntr_d(char *input, t_data **data);

int				get_unquoted_size(char *str, char quote);
char			*remove_single_quotes(char *str);
char			*remove_double_quotes(char *str);
int				add_token(t_tokens **head, char *str, t_type type);
t_tokens		*get_tokens(t_data *data, char *str);
bool			is_there_quotes(char *str);
int				get_next_quote(char *str, int begin, char quote);
void			add_list(t_data *data, t_varlst *temp_var);
void			get_type_input(t_tokens *temp);
void			remove_node(t_tokens **head, t_tokens *node_to_remove);
void			remove_head_quotes(t_tokens *head, t_data *data);
void			remove_quotes(t_tokens *head, t_data *data);
int				get_word_until(char *str, int i, t_tokens **head);
int				get_new_token(char *str, int i, t_tokens **head);
t_type			is_there_token(char c);
char			*cut_quotes_all(char *input);

void			free_unset(t_varlst *temp, t_varlst *temp_var);
void			exec_unset(t_data *data, char **input);

bool			check_non_numeric(char *str);
bool			check_pipes(char *str, int i);
bool			check_closed_quotes(const char *input, int i_str);
int				get_len_pipes(char *input);
int				len_data(t_tokens *tokens);
int				len_strings(char **cmd);
void			print_string(char **str);
void			print_export_value(char **str);
char			check_quote(char *str);
char			*ft_mllstrcpy(char *str);
long long int	ft_atoll(const char *str);
char			*ft_mllstrcat(char *str1, char *str2, char c);

#endif
