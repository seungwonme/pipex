/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:45:49 by seunan            #+#    #+#             */
/*   Updated: 2024/03/30 18:46:25 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"
#include "safe_syscalls.h"
#include "utils.h"

static void	infile_to_pipe(t_vars *vars);
static void	pipe_to_pipe(t_vars *vars, int i);
static void	pipe_to_outfile(t_vars *vars);
static void	run_cmd_with_io_redir(char **path, char *cmd, \
	int in_fd, int out_fd);

void	pipex(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->argc - 3)
	{
		if (i == 0)
			infile_to_pipe(vars);
		else if (i == vars->argc - 4)
			pipe_to_outfile(vars);
		else
			pipe_to_pipe(vars, i);
		++i;
	}
	i = 0;
	while (i < vars->argc - 3)
	{
		waitpid(-1, NULL, 0);
		++i;
	}
}

void	infile_to_pipe(t_vars *vars)
{
	pid_t	pid;

	safe_pipe(vars->fd);
	pid = safe_fork();
	if (pid == 0)
	{
		close(vars->fd[READ_END]);
		if (vars->infile == 0)
			vars->infile = safe_open(vars->argv[1], O_RDONLY, 0644);
		run_cmd_with_io_redir(vars->path, vars->argv[2], \
			vars->infile, vars->fd[WRITE_END]);
	}
	if (vars->infile != 0)
		safe_close(vars->infile);
	safe_close(vars->fd[WRITE_END]);
}

void	pipe_to_pipe(t_vars *vars, int i)
{
	int		prev_fd;
	pid_t	pid;

	prev_fd = vars->fd[READ_END];
	safe_pipe(vars->fd);
	pid = safe_fork();
	if (pid == 0)
	{
		safe_close(vars->fd[READ_END]);
		run_cmd_with_io_redir(vars->path, vars->argv[2 + i], \
			prev_fd, vars->fd[WRITE_END]);
	}
	safe_close(vars->fd[WRITE_END]);
	safe_close(prev_fd);
}

void	pipe_to_outfile(t_vars *vars)
{
	int		outfile;
	pid_t	pid;

	pid = safe_fork();
	if (pid == 0)
	{
		if (vars->infile == 0)
			outfile = safe_open(vars->argv[vars->argc - 1], \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			outfile = safe_open(vars->argv[vars->argc - 1], \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		run_cmd_with_io_redir(vars->path, vars->argv[vars->argc - 2], \
			vars->fd[READ_END], outfile);
	}
	safe_close(vars->fd[READ_END]);
}

void	run_cmd_with_io_redir(char **path, char *cmd, int in_fd, int out_fd)
{
	char	**cmd_argv;

	safe_dup2(in_fd, STDIN_FILENO);
	safe_dup2(out_fd, STDOUT_FILENO);
	cmd_argv = ft_split(cmd, ' ', '\0');
	*cmd_argv = find_executable_path(path, *cmd_argv);
	if (execve(*cmd_argv, cmd_argv, NULL) == -1)
		ft_error(*cmd_argv);
}
