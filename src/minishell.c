/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:34:00 by marvin            #+#    #+#             */
/*   Updated: 2023/05/08 17:34:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void iniciar(void)
{
	printf("minishell$>");
}

void init()
{
	while(1)
	{
		iniciar();
		//wait();
		sleep(10000);
	}
	return ;
}
