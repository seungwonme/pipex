/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 23:51:55 by seunan            #+#    #+#             */
/*   Updated: 2023/09/07 22:42:51 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"

char	**parse_path(char *envp[])
{
	char	**path;
	char	*tmp;
	int		i;

	path = NULLPTR;
	i = 0;
	while (envp != NULLPTR && envp[i] != NULLPTR)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tmp = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			path = ft_split(tmp, ':', '\0');
			free(tmp);
			break ;
		}
		++i;
	}
	return (path);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULLPTR)
	{
		free(path[i]);
		++i;
	}
	free(path);
}

void	protected_pipe(int fd[2])
{
	if (pipe(fd) < 0)
		ft_error("pipe");
}

pid_t	protected_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	return (pid);
}

void	protected_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) < 0)
		ft_error("dup2");
}

/* 
1. 
pipe(fd[0])
fork()
close(fd[0][WRITE_END])

2. 
pipe(fd[1])
fork()
close(fd[0][WRITE_END])

3.
close(fd[0][READ_END])
pipe(fd[0])
fork()
close(fd[0][WRITE_END])

1.
close(fd[0][READ_END])
dup2(infile, STDIN_FILENO)
dup2(fd[0][WRITE_END], STDOUT_FILENO)

2.
close(fd[1][READ_END])
dup2(fd[0][READ_END], STDIN_FILENO)
dup2(fd[1][WRITE_END], STDOUT_FILENO)
 */
