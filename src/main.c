/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:47:33 by seunan            #+#    #+#             */
/*   Updated: 2023/09/09 16:01:52 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int ac, char *av[], char *envp[])
{
	if (ac < 5)
		ft_error("Usage: ./pipex [infile] [cmd 1] ... [cmd n] [outfile]");
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		
	pipex(ac, av, envp);
	return (0);
}
