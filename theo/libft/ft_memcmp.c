/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:40:34 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/11 14:06:53 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return ((int)(((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]));
}
/*
int	main(int ac, char **av)
{
	if (ac != 3)
	{
		printf("ERROR");
		return (0);
	}
	else
		printf("%d", (memcmp((const void *)av[1], (const void *)av[2], 4)));
	return (0);
}*/
