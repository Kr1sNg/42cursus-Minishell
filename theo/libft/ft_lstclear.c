/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:37:20 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/14 15:37:23 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*temp;

	ptr = *lst;
	temp = NULL;
	while (ptr)
	{
		temp = ptr->next;
		(del)(ptr->content);
		free(ptr);
		ptr = temp;
	}
	*lst = NULL;
}
