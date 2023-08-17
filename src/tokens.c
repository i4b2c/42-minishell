#include "../include/minishell.h"

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
			if(!ft_strncmp(command[i],">>",3))
				type = RDR_AP_OUT;
			else if(ft_strchr(command[i],'>'))
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