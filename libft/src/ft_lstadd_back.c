/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:39:30 by seunan            #+#    #+#             */
/*   Updated: 2024/01/01 19:59:41 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (lst == NULLPTR || new == NULLPTR)
		return ;
	if (*lst == NULLPTR)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	tmp = ft_lstlast(tmp);
	tmp->next = new;
}
