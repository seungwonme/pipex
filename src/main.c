#include "here_doc.h"
#include "libft.h"
#include "pipex.h"
#include "safe_syscalls.h"
#include "utils.h"

// TEST
#include <stdio.h>
#include <stdlib.h>
// export MallocStackLogging=1 when you're finished unset MallocStackLogging.
// To view detailed information about leaks, use the gcc -g option.
// while true; do leaks a.out; sleep 1; done;
void	leak(void)
{
	system("leaks --list pipex");
}
// TEST

int	main(int argc, char *argv[], char *envp[])
{
	// atexit(leak);
	t_vars vars;

	if (argc < 5)
		invalid_args();
	vars = init_vars(argc, argv, envp);
	if (ft_strncmp(vars.argv[1], "here_doc", 9) == 0)
		here_doc(&vars);
	else
		pipex(&vars);
	free_path(vars.path);
	return 0;
}
