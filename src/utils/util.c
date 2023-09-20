/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:21:18 by icaldas           #+#    #+#             */
/*   Updated: 2023/09/06 16:21:18 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_mllstrcpy(char *str)
{
	int		i;
	int		len;
	char	*temp;

	i = 0;
	len = ft_strlen(str);
	temp = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		temp[i] = str[i];
		i++;
	}
	temp[i] = 0;
	return (temp);
}

long long int	ft_atoll(const char *str)
{
	long long int			result;
	int						sign;

	result = 0;
	sign = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return ((long long int)result * sign);
}

char	*ft_mllstrcat(char *str1, char *str2, char c)
{
	char	*temp;
	int		i1;
	int		i2;

	if (!str1)
		return (ft_mllstrcpy(str2));
	if (!c)
		temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	else
		temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
	i1 = -1;
	while (str1[++i1])
		temp[i1] = str1[i1];
	if (c)
		temp[i1++] = c;
	i2 = -1;
	while (str2[++i2])
		temp[i1 + i2] = str2[i2];
	temp[i1 + i2] = 0;
	return (temp);
}
