/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 00:12:59 by sunko             #+#    #+#             */
/*   Updated: 2024/01/01 20:00:48 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	ft_error(const char* msg)
{
	ft_putstr_fd("\033[0;31m", STDERR_FILENO);
	ft_putstr_fd("Pipex: ", STDERR_FILENO);
	perror(msg);
	ft_putstr_fd("\033[0m", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
