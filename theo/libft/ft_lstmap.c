/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:08:47 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/14 16:37:42 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstdest;
	t_list	*ptr;
	t_list	*odest;

	ptr = NULL;
	lstdest = NULL;
	if (!lst)
		return (NULL);
	ptr = lst;
	lstdest = ft_lstnew((f)(lst->content));
	if (!lstdest)
		return (NULL);
	odest = lstdest;
	while (ptr->next)
	{
		lstdest->next = (t_list *)malloc(sizeof(t_list));
		if (!(lstdest->next))
			ft_lstclear(&odest, (del));
		ptr = ptr->next;
		lstdest = lstdest->next;
		lstdest->content = (f)(ptr->content);
		lstdest->next = NULL;
	}
	return (odest);
}
