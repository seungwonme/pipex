/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:46:43 by seunan            #+#    #+#             */
/*   Updated: 2024/03/30 18:48:52 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "utils.h"

void	free_path(char **path)
{
	int	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		free(path[i]);
		++i;
	}
	free(path);
}

void	invalid_args(void)
{
	ft_putstr_fd("\033[0;31m", STDERR);
	ft_putstr_fd("Usage: ./pipex infile cmd1 ... cmdn outfile\n", STDERR);
	ft_putstr_fd("\033[0m", STDERR);
	exit(FAILURE);
}

char	**get_path(char *envp[])
{
	if (!envp)
		return (NULL);
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return ((char **)ft_split(*envp + 5, ':', '/'));
		++envp;
	}
	return (NULL);
}

t_vars	init_vars(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	vars.path = get_path(envp);
	vars.argv = argv;
	vars.argc = argc;
	vars.infile = 0;
	return (vars);
}

char	*find_executable_path(char **path, char *cmd)
{
	char	*path_cmd;

	if (!path)
		return (cmd);
	while (*path)
	{
		path_cmd = ft_strjoin(*path, cmd);
		if (access(path_cmd, X_OK) == 0)
		{
			free(cmd);
			return (path_cmd);
		}
		free(path_cmd);
		++path;
	}
	return (cmd);
}
