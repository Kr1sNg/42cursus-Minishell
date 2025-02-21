/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:47:27 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/12 20:34:47 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memcpy(void *s, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!s && !src && n > 0)
		return (NULL);
	while (i < n)
	{
		((unsigned char *) s)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	int array[] = {54, 85, 20, 63, 21};
	int array2[] = {34, 23, 12, 43, 1};
	size_t size = sizeof(int) * 5;
	int length;

	length = 0;
	while (length < 5)
	{
		printf("%d ", array[length]);
		length++;
	}
	printf( "\n" );
	ft_memcpy( array, array2, size);
	length = 0;
	while (length < 5)
	{
		printf("%d ", array[length]);
		length++;
	}
	printf( "\n" );
    	return 0;
}*/
