/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:52:08 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/14 16:38:59 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = NULL;
	if (nmemb * size > 2147483647 || nmemb == 0 || size == 0)
	{
		ptr = malloc(1);
		((unsigned char *)ptr)[0] = '\0';
		return (ptr);
	}
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (((unsigned char *)ptr)[i])
	{
		((unsigned char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}
/*
int	main(void)
{
	int	*tab;
	
	tab = ft_calloc(4, sizeof(int));
	free(tab);
	return (0);
}*/
