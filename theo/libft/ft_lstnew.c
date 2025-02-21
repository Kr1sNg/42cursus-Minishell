/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:40:40 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/13 15:16:28 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*up;

	up = (t_list *)malloc(sizeof(t_list));
	if (!up)
		return (NULL);
	up->content = content;
	up->next = NULL;
	return (up);
}
