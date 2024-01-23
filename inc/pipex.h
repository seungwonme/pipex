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

enum e_pipe
{
	READ_END = 0,
	WRITE_END = 1
};

// utils.c
char	**parse_path(char *envp[]);
void	free_path(char **path);
void	protected_pipe(int fd[2]);
pid_t	protected_fork(void);
void	protected_dup2(int oldfd, int newfd);

// pipex.c
void	pipex(char *av[], char *envp[]);
void	infile_to_fd(char *av[], char *path[], int fd[2]);
void	fd_to_outfile(char *av[], char *path[], int fd[2]);
char	*path_join(char *path[], char *cmd);

#endif
