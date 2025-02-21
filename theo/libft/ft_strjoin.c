/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:16:26 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/21 01:05:25 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static char	*ft_strcpy_join(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*ptr;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	ptr = malloc((lens1 + lens2) * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	ft_strcpy_join(ptr, (char *) s1);
	ft_strcpy_join(ptr, (char *) s2);
	return (ptr);
}
/*
int	main(int ac, char **av)
{
	char	*ptr;

	ptr = NULL;
	if (ac != 3)
		return (0);
	else
	{
		ptr = ft_strjoin((char const *)av[1], (char const *)av[2]);
		printf("%s", ptr);
		free(ptr);
	}
	return (0);
}*/
