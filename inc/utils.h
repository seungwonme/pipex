#ifndef UTILS_H
#define UTILS_H

#include "pipex.h"

void	free_path(char** path);
void	invalid_args(void);
char**	get_path(char *envp[]);
t_vars	init_vars(int argc, char *argv[], char *envp[]);
char*	find_executable_path(char** path, char* cmd);

#endif
