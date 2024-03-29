#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "pipex.h"
#include "safe_syscalls.h"
#include "utils.h"

static void	infile_to_pipe(t_vars* vars);
static void	pipe_to_pipe(t_vars* vars, int i);
static void	pipe_to_outfile(t_vars* vars);

void	pipex(t_vars* vars)
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

void	infile_to_pipe(t_vars* vars)
{
	int		infile;
	pid_t	pid;
	char**	cmd_argv;

	safe_pipe(vars->fd);
	pid = safe_fork();
	if (pid == 0)
	{
		close(vars->fd[READ_END]);
		infile = safe_open(vars->argv[1], O_RDONLY, 0644);
		safe_dup2(infile, STDIN_FILENO);
		safe_dup2(vars->fd[WRITE_END], STDOUT_FILENO);
		cmd_argv = ft_split(vars->argv[2], ' ', '\0');
		*cmd_argv = find_executable_path(vars->path, *cmd_argv);
		if (execve(*cmd_argv, cmd_argv, NULL) == -1)
			ft_error("Failed to execute command");
	}
	safe_close(vars->fd[WRITE_END]);
}

void	pipe_to_pipe(t_vars* vars, int i)
{
	int		prev_fd;
	pid_t	pid;
	char**	cmd_argv;

	prev_fd = vars->fd[READ_END];
	safe_pipe(vars->fd);
	pid = safe_fork();
	if (pid == 0)
	{
		safe_close(vars->fd[READ_END]);
		safe_dup2(prev_fd, STDIN_FILENO);
		safe_dup2(vars->fd[WRITE_END], STDOUT_FILENO);
		cmd_argv = ft_split(vars->argv[2 + i], ' ', '\0');
		*cmd_argv = find_executable_path(vars->path, *cmd_argv);
		if (execve(*cmd_argv, cmd_argv, NULL) == -1)
			ft_error("Failed to execute command");
	}
	safe_close(vars->fd[WRITE_END]);
	safe_close(prev_fd);
}

void	pipe_to_outfile(t_vars* vars)
{
	int		outfile;
	pid_t	pid;
	char**	cmd_argv;

	pid = safe_fork();
	if (pid == 0)
	{
		outfile = safe_open(vars->argv[vars->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		safe_dup2(vars->fd[READ_END], STDIN_FILENO);
		safe_dup2(outfile, STDOUT_FILENO);
		cmd_argv = ft_split(vars->argv[vars->argc - 2], ' ', '\0');
		*cmd_argv = find_executable_path(vars->path, *cmd_argv);
		if (execve(*cmd_argv, cmd_argv, NULL) == -1)
			ft_error("Failed to execute command");
	}
	safe_close(vars->fd[READ_END]);
}
