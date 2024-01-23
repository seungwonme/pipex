/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunan <seunan@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:46:05 by seunan            #+#    #+#             */
/*   Updated: 2024/01/01 19:59:58 by seunan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*head;

	if (lst == NULLPTR || f == NULLPTR || del == NULLPTR)
		return (NULLPTR);
	tmp = ft_calloc(1, sizeof(t_list));
	if (tmp == NULLPTR)
		return (NULLPTR);
	head = tmp;
	while (lst->next != NULLPTR)
	{
		tmp->content = f(lst->content);
		tmp->next = ft_calloc(1, sizeof(t_list));
		if (tmp->next == NULLPTR)
		{
			ft_lstclear(&head, del);
			return (NULLPTR);
		}
		tmp = tmp->next;
		lst = lst->next;
	}
	tmp->content = f(lst->content);
	return (head);
}
