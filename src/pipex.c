/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:36:27 by seunan            #+#    #+#             */
/*   Updated: 2023/09/09 19:54:35 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "pipex.h"
#include "utils.h"

// ./pipex infile cmd cmd outfile 
// cmd cnt = ac - 3
void	pipex(int ac, char *av[], char *envp[])
{
	(void) ac;
	char	**path;
	pid_t	pid[ac - 3];
	int		fd[2][2];

	path = parse_path(envp);
	protected_pipe(fd);
	pid[0] = protected_fork();
	if (pid[0] == 0)
		infile_to_fd(av, path, fd);
	pid[1] = protected_fork();
	if (pid[1] == 0)
		fd_to_outfile(av, path, fd);
	waitpid(pid[0], NULLPTR, 0);
	waitpid(pid[1], NULLPTR, 0);
	free_path(path);
}

void	infile_to_fd(char *av[], char *path[], int fd[2])
{
	int		infile;
	char	**execve_argv;
	char	*execve_path;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		ft_error(av[1]);
	if (close(fd[READ_END]) < 0)
		ft_error("close");
	execve_argv = ft_split(av[2], ' '. '/');
	execve_path = path_join(path, execve_argv[0]);
	protected_dup2(infile, STDIN_FILENO);
	protected_dup2(fd[WRITE_END], STDOUT_FILENO);
	if (execve(execve_path, execve_argv, NULLPTR) < 0)
		ft_error(ft_strjoin(av[2], ": command not founds"));
}

void	fd_to_outfile(char *av[], char *path[], int fd[2])
{
	int		outfile;
	char	**execve_argv;
	char	*execve_path;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile < 0)
		ft_error(av[4]);
	if (close(fd[WRITE_END]) < 0)
		ft_error("close");
	execve_argv = ft_split(av[3], ' ', '/');
	execve_path = path_join(path, execve_argv[0]);
	protected_dup2(fd[READ_END], STDIN_FILENO);
	protected_dup2(outfile, STDOUT_FILENO);
	if (execve(execve_path, execve_argv, NULLPTR) < 0)
		ft_error(ft_strjoin(av[3], ": command not found"));
}

char	*path_join(char *path[], char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path != NULLPTR && path[i] != NULLPTR)
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		++i;
	}
	if (path[i] == NULLPTR)
		return (cmd);
	return (tmp);
}
