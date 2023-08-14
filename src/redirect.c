#include "../include/minishell.h"

char *change_stdout(char *input)
{
	char **split_command;
	char *command_trim;
	int fd;
	char *new_input;

	split_command = ft_split(input,'>');
	command_trim = ft_strtrim(split_command[1],"\t ");
	fd = open(command_trim,O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd,STDOUT_FILENO);
	free(input);
	new_input = malloc(sizeof(char) * (ft_strlen(split_command[0]) + 1));
	ft_strcpy(new_input,split_command[0]);
	free_strings(split_command);
	free(command_trim);
	return (new_input);
}
