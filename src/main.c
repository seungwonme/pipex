/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:41:01 by seunan            #+#    #+#             */
/*   Updated: 2024/03/30 18:42:13 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"
#include "libft.h"
#include "pipex.h"
#include "safe_syscalls.h"
#include "utils.h"
#include <stdlib.h>

/* void	leak(void)
{
	system("leaks --list pipex");
	atexit(leak);
} */

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	if (argc < 5)
		invalid_args();
	vars = init_vars(argc, argv, envp);
	if (ft_strncmp(vars.argv[1], "here_doc", 9) == 0)
		here_doc(&vars);
	else
		pipex(&vars);
	free_path(vars.path);
	return (0);
}
