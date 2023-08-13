#include "../include/minishell.h"

void	ft_strcpy_path(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 5;
	j = 0;
	while (s2[i] != 0)
	{
		s1[j] = s2[i];
		i++;
		j++;
	}
}

char	**getpath(char **str)
{
	int		i;
	char	*path_simple;
	char	**path;

	i = 0;
	while (str[i] != NULL)
	{
		if (!(ft_strncmp("PATH=", str[i], 5)))
		{
			path_simple = malloc(ft_strlen(str[i]));
			ft_strcpy_path(path_simple, str[i]);
		}
		i++;
	}
	path = NULL;
	path = ft_split(path_simple, ':');
	free(path_simple);
	return (path);
}

char	*check_command(char *command, char **path)
{
	char	*teste;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		teste = malloc(256);
		ft_strcpy(teste, path[i]);
		ft_strlcat(teste, "/", 256);
		ft_strlcat(teste, command, 256);
		if (access(teste, X_OK) == 0)
			return (teste);
		i++;
		free(teste);
	}
	return (NULL);
}

void	exec(char *command)
{
	char	*path;
	char	*check;
	char	**cmd;

	cmd = ft_split(command, ' ');
	path = getenv("PATH");
	check = check_command(cmd[0], ft_split(path,':'));
	if (check != NULL)
		execve(check, cmd, NULL);
	if(access(cmd[0],X_OK) == 0)
		execve(cmd[0],cmd, NULL);
	write(2,"minishell : command not found\n",30);
	free(command);
	exit(0);
}
