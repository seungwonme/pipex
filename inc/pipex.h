#ifndef PIPEX_H
# define PIPEX_H

typedef enum e_pipe
{
	READ_END = 0,
	WRITE_END = 1
} t_pipe;

typedef struct s_vars
{
	char**	path; // NULL or PATH
	char**	argv;
	int		argc;
	int		infile;
	int		fd[2];
} t_vars;

void	pipex(t_vars* vars);

#endif
