#include "../include/minishell.h"

char	*ft_mllstrcpy(char *str)
{
	int i;
	int len;
	char *temp;

	i = 0;
	len = ft_strlen(str);
	temp = malloc(sizeof(char) * (len + 1));
	while(str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return temp;
}

void	add_list(t_data *data, t_varlst *temp_var)
{
		t_varlst *atual;

		atual = NULL;
		if(data->var_head == NULL)
			data->var_head = temp_var;
		else
		{
			atual = data->var_head;
			while(atual->next != NULL)
				atual = atual->next;
			atual->next = temp_var;
		}
}
