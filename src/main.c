#include "../include/minishell.h"

volatile long long	g_exit_status = 0;

char *change_stdin(char *input)
{
	char **command;
	char *command_trim;
	char *new_input;
	int fd;

	command = ft_split(input,'<');
	command_trim = ft_strtrim(command[1]," \t");
	fd = open(command_trim,O_RDONLY);
	free(input);
	if(fd == -1)
	{
		free_strings(command);
		free(command_trim);
		perror("minishell: ");
		return (NULL);
	}
	dup2(fd,STDIN_FILENO);
	new_input = ft_mllstrcpy(command[0]);
	free_strings(command);
	free(command_trim);
	return (new_input);
}

// void get_bt(t_data *data)
// {
// 	t_btcommand *temp_bt;

// 	temp_bt = data->bt_head;
// 	while()
// }

void add_token(t_tokens **head, char *str,t_type type)
{
    t_tokens *new_token = malloc(sizeof(t_tokens));
	t_tokens *temp;
    if (!new_token) {
        return;
    }

    new_token->command = ft_mllstrcpy(str);
	new_token->type = type;
    new_token->next = NULL;

    if (!*head) {
        *head = new_token;
    }
	else
	{
		temp = *head;
		while (temp->next) {
			temp = temp->next;
	}
		temp->next = new_token;
	}
}

t_tokens *tokens_input(char *input)
{
	t_tokens *temp;
	t_type type;
	char **command;
	int i;

	i = 0;
	command = ft_split(input,' ');
	temp = NULL;
	type = NORMAL;
	while(command[i])
	{
		if(!ft_strchr(command[i],'>')
			&& !ft_strchr(command[i],'<'))
		{
			add_token(&temp,command[i],type);
			i++;
		}
		else
		{
			if(ft_strchr(command[i],'>'))
				type = RDR_OUT;
			else
				type = RDR_IN;
			i++;
		}
	}
	free_strings(command);
	free(input);
	return temp;
}

void print_tokens(t_tokens *head)
{
	t_tokens *temp;

	temp = head;
	while(temp)
	{
		printf("%s\n",temp->command);
		printf("%d\n\n",temp->type);
		temp = temp->next;
	}
}

void exec_tokens(t_data *data)
{
	char **command;
	int len;
	t_tokens *temp;
	int i;
	pid_t pid;

	i = 0;
	temp = data->tokens_head;
	len = 0;
	while(temp)
	{
		temp = temp->next;
		len++;
	}
	command = malloc(sizeof(char *) * (len + 1));
	temp = data->tokens_head;
	while(temp)
	{
		if(temp->type == NORMAL)
		{
			command[i] = ft_mllstrcpy(temp->command);
			i++;
		}
		else if(temp->type == RDR_OUT)
		{
			int fd_out = open(temp->command, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			dup2(fd_out,STDOUT_FILENO);
		}
		else if(temp->type == RDR_IN)
		{
			int fd_in = open(temp->command,O_RDONLY);
			dup2(fd_in,STDIN_FILENO);
		}
		temp = temp->next;
	}
	command[i] = NULL;
	if(!ft_strncmp(command[0],"export",6))
	{
		if(data->tokens_head->next != NULL
			&& data->tokens_head->next->type == NORMAL)
			change_env(data,command);
		else
			print_export(data);
	}
	else if(!ft_strncmp(command[0],"unset",5))
		exec_unset(data,command);
	else if(!ft_strncmp(command[0],"cd",2))
		exec_chdir(command);
	else if(!strncmp(command[0],"env",3))
		print_env(data);
	else if(!strncmp(command[0],"echo",4))
		exec_echo(data,command);
	// else if(command[0][0])
	// 	continue ;
	else
	{
		pid = fork();
		if(pid == 0)
			execve_tokens(command,data);
		else
			waitpid(pid,NULL,0);
	}
}
void free_tokens(t_data *data)
{
	t_tokens *temp_tokens;

	while(data->tokens_head != NULL)
	{
		temp_tokens = data->tokens_head->next;
		free(data->tokens_head->command);
		free(data->tokens_head);
		data->tokens_head = temp_tokens;
	}
	data->tokens_head = NULL;
}


int main(int ac, char **av, char **envp)
{
	t_data *data;
	char *input;
	int temp_stdout;
	int temp_stdin;

	if(ac > 1 && av)
		error(ARGS,NULL);
	data = get_data(ac,av,envp);
	init_signal();
	temp_stdout = dup(STDOUT_FILENO);
	temp_stdin = dup(STDIN_FILENO);
	while(1)
	{
		dup2(temp_stdout,STDOUT_FILENO);
		dup2(temp_stdin,STDIN_FILENO);
		input = get_input();
		add_history(input);
		data->tokens_head = tokens_input(input);
		if(!strncmp(data->tokens_head->command,"exit",4))
		{
			free_data(&data);
			break;
		}
		exec_tokens(data);
		free_tokens(data);

		//printf("%s\n",data->tokens_head->command);
		//get_bt(data);
		// add_history(input);
		// if(!strcmp(input,"exit"))
		// {
		// 	free(input);
		// 	free_data(&data);
		// 	break;
		// }
		// else if(ft_strchr(input,'>'))
		// 	input = change_stdout(input);
		// else if(ft_strchr(input,'<'))
		// 	input = change_stdin(input);
		// if(input != NULL)
		// 	check_exec(data,input);
	}
	return 0;
}
