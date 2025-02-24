/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:31:29 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/12 20:17:23 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_checktrim(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = NULL;
	len = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	while (ft_checktrim(s1[i], set) == 1 && i < len)
		i++;
	while (ft_checktrim(s1[len - 1], set) == 1 && len > i)
		len--;
	ptr = malloc(sizeof(char) * (len - i + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[j++] = s1[i++];
	}
	ptr[j] = '\0';
	return (ptr);
}
/*
int	main (void)
{
	char	*dest;

	dest = ft_strtrim("\t   \nt\n\n  \n\n\t   ", " \n\t");
	printf("%s", dest);
	free(dest);
	return (0);
}*/
