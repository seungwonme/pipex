/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 18:51:12 by seunan            #+#    #+#             */
/*   Updated: 2024/03/30 18:51:21 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "pipex.h"

typedef struct s_here_doc
{
	char	*limiter;
	char	*tmp_file;
	int		tmp_fd;
}	t_here_doc;

void	here_doc(t_vars *vars);

#endif
