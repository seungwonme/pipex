/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:50:04 by seunan            #+#    #+#             */
/*   Updated: 2024/03/30 18:51:09 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef enum e_pipe
{
	READ_END = 0,
	WRITE_END = 1
}	t_pipe;

typedef struct s_vars
{
	char	**path;
	char	**argv;
	int		argc;
	int		infile;
	int		fd[2];
}	t_vars;

void	pipex(t_vars *vars);

#endif
