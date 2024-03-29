#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "safe_syscalls.h"

int	safe_open(const char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd == -1)
	{
		ft_error("Failed to open file");
	}
	return (fd);
}

int	safe_close(int fd)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
	{
		ft_error("Failed to close file");
	}
	return (ret);
}

int	safe_dup2(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret == -1)
	{
		ft_error("Failed to duplicate file descriptor");
	}
	return (ret);
}

int	safe_pipe(int pipefd[2])
{
	int	ret;

	ret = pipe(pipefd);
	if (ret == -1)
	{
		ft_error("Failed to create pipe");
	}
	return (ret);
}

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_error("Failed to fork process");
	}
	return (pid);
}
