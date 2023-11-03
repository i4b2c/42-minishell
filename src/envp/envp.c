/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:22:24 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 14:22:24 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern volatile long long	g_exit_status;

bool	check_exist_env(t_data *data, char *input)
{
	t_varlst	*temp_var;

	temp_var = data->var_head;
	while (temp_var)
	{
		if (!ft_strncmp(temp_var->var_name, input, ft_strlen(input) + 1))
			return (true);
		temp_var = temp_var->next;
	}
	return (false);
}

void	change_exist_env(t_data *data, char **command)
{
	t_varlst	*temp_var;

	temp_var = data->var_head;
	if (!command[1])
		return ;
	while (temp_var)
	{
		if (!ft_strncmp(temp_var->var_name, command[0], ft_strlen(command[0])))
		{
			if (temp_var->var_value)
			{
				free(temp_var->var_value);
				temp_var->var_value = ft_mllstrcpy(command[1]);
			}
			else
				temp_var->var_value = ft_mllstrcpy(command[1]);
			return ;
		}
		temp_var = temp_var->next;
	}
	return ;
}

bool	check_input_env(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]))
		return (true);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (true);
		i++;
	}
	return (false);
}

void	check_exist(t_data *data, char *input,
	char **command, t_varlst *temp_var)
{
	if (check_exist_env(data, command[0]))
	{
		if (!command[1] && ft_strchr(input, '='))
		{
			command[1] = ft_calloc(1, 1);
			command[2] = NULL;
		}
		free(temp_var);
		change_exist_env(data, command);
	}
	else
	{
		temp_var->var_name = ft_mllstrcpy(command[0]);
		if (command[1])
			temp_var->var_value = ft_mllstrcpy(command[1]);
		else if (!ft_strchr(input, '='))
			temp_var->var_value = NULL;
		else
			temp_var->var_value = ft_calloc(1, 1);
		temp_var->next = NULL;
		add_list(data, temp_var);
		temp_var = temp_var->next;
	}
}

void	change_env(t_data *data, char **input)
{
	t_varlst	*temp_var;
	char		**command;
	int			j;

	j = 0;
	while (input[++j])
	{
		if (check_input_env(input[j]))
		{
			write(2, "not a valid identifier\n", 24);
			g_exit_status = 1;
		}
		else
		{
			temp_var = malloc(sizeof(t_varlst));
			if (!temp_var)
				error(MALLOC, 0);
			command = ft_split(input[j], '=');
			check_exist(data, input[j], command, temp_var);
			free_strings(command);
			free(command);
		}
	}
}
