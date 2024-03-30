/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:49:15 by seunan            #+#    #+#             */
/*   Updated: 2024/03/30 18:49:50 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "pipex.h"

void	free_path(char **path);
void	invalid_args(void);
char	**get_path(char *envp[]);
t_vars	init_vars(int argc, char *argv[], char *envp[]);
char	*find_executable_path(char **path, char *cmd);

#endif
