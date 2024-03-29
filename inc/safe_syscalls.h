#ifndef SAFE_SYSCALLS_H
#define SAFE_SYSCALLS_H

#include <sys/types.h>

int	safe_open(const char *pathname, int flags, mode_t mode);
int	safe_close(int fd);
int	safe_dup2(int oldfd, int newfd);
int	safe_pipe(int pipefd[2]);
int	safe_fork(void);

#endif
