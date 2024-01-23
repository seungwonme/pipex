/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 07:50:57 by seunan            #+#    #+#             */
/*   Updated: 2023/09/06 18:14:06 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// utils.c
char	**parse_path(char *envp[]);
void	free_path(char **path);
void	protected_pipe(int fd[2]);
pid_t	protected_fork(void);
void	protected_dup2(int oldfd, int newfd);

#endif
