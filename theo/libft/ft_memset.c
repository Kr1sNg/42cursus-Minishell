/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:50:51 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/08 11:03:26 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	int array [] = { 54, 85, 20, 63, 21 };
	size_t size = sizeof(int) * 5;
	int length;

	length = 0;
	while (length < 5)
	{
		printf("%d ", array[length]);
		length++;
	}
	printf( "\n" );
	ft_memset( array, 256, size);
	length = 0;
	while (length < 5)
	{
		printf("%d ", array[length]);
		length++;
	}
    printf( "\n" );

    return 0;
}*/
