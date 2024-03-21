/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 07:50:57 by seunan            #+#    #+#             */
/*   Updated: 2023/09/06 18:14:06 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <sys/types.h>

typedef struct s_info	t_info;
typedef enum e_pipe		t_pipe;

struct s_info
{
	int		ac;
	char	**av;
	char	**path;
	pid_t	*pid;
	int		fd[2][2];
};

enum e_pipe
{
	READ_END = 0,
	WRITE_END = 1
};

// pipex.c
void	pipex(int ac, char *av[], char *envp[]);
void	infile_to_fd(char *av[], char *path[], int fd[2]);
void	fd_to_outfile(char *av[], char *path[], int fd[2]);
char	*path_join(char *path[], char *cmd);

#endif
