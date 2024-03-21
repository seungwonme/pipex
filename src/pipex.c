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

void	init_info(int ac, char *av[], char *envp[])
{
	info.ac = ac;
	info.av = av;
	info.path = parse_path(envp);
	info.pid = (pid_t *)malloc(sizeof(pid_t) * (ac - 3));
	protected_pipe(info.fd[0]);
	protected_pipe(info.fd[1]);
}

void	redirect_io(t_info* info, int i)
{
	if (i == 0)
		infile_to_pipe(info->av, info->path, info->fd[0]);
	else if (i == info->ac - 4)
		pipe_to_outfile(info->av, info->path, info->fd[1]);
	else
	{
		// 중간 명령어 실행
	}
}

void	execute_cmd(t_info* info, int i)
{
	char	**execve_argv;
	char	*execve_path;

	info->pid[i] = protected_fork();
	if (info->pid[i] == 0)
	{
		execve_argv = ft_split(av[2], ' ', '/');
		execve_path = path_join(path, execve_argv[0]);
		redirect_io(info, i);
		if (execve(execve_path, execve_argv, NULL) < 0)
		{
			ft_putstr("\033[0;31mpipex: av[3]: ");
			ft_error(ft_strjoin(av[3], ": command not found"));
		}
	}
}

void	pipex(int ac, char *av[], char *envp[])
{
	t_info	info;
	int		i;

	init_info(ac, av, envp);
	i = 0;
	while (i < ac - 3)
	{
		execute_cmd(&info, i);
		++i;
	}
	// free_info(&info);
}

/* 
상황에 맞는 fd로 dup2를 통해 입력 흐름 제어하는 함수 (자식 프로세스)
 */

char	*path_join(char *path[], char *cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, X_OK) == 0)
			break ;
		free(tmp);
		++i;
	}
	if (path == NULL || path[i] == NULL)
		return (cmd);
	return (tmp);
}

void	infile_to_pipe(char *av[], char *path[], int fd[2])
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
	if (execve(execve_path, execve_argv, NULL) < 0)
		ft_error(ft_strjoin(av[2], ": command not founds"));
}

void	pipe_to_outfile(char *av[], char *path[], int fd[2])
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
	if (execve(execve_path, execve_argv, NULL) < 0)
		ft_error(ft_strjoin(av[3], ": command not found"));
}
