/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:07:31 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/12 20:32:42 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src && n != 0)
		return (NULL);
	if (src + n >= dest && dest > src)
	{
		while (n > 0)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	else
	{
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	char	str[23] = "rem ipssum dolor sit a";
	char	str2[23];
	size_t size = 8;
	int length;

	length = 0;
	while (length < 8)
	{
		printf("%c", str[length]);
		length++;
	}
	printf( "\n" );
	ft_memmove(str2, str, size);
	length = 0;
	while (length < 8)
	{
		printf("%c", str[length]);
		length++;
	}
	printf( "\n" );
	return 0;
}*/
