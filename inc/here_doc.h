#ifndef HERE_DOC_H
#define HERE_DOC_H

#include "pipex.h"

typedef struct s_here_doc
{
	char*	limiter;
	char*	tmp_file;
	int		tmp_fd;
}	t_here_doc;

void	here_doc(t_vars* vars);

#endif
