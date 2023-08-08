/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaldas <icaldas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 13:32:25 by icaldas           #+#    #+#             */
/*   Updated: 2023/07/26 13:32:33 by icaldas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/src/libft.h"
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

/* utils */
void	ft_strcpy_path(char *s1, char *s2);
char	**getpath(char **str);
char	*check_command(char *command, char **path);
void	error(void);

/* pipex */
void	exec(char *command, char **envp);
void	child_process(char **av, char **envp, int fd[2]);
void	parent_process(char **av, char **envp, int fd[2]);
void	pipex(char **av, char **envp);


#endif
