/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:15:18 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/12 14:37:05 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static size_t	ft_len(char const *s, unsigned int start, size_t len)
{
	if (start > ft_strlen(s))
		return (0);
	if (ft_strlen(s) - start < len)
		return (ft_strlen(s) - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = malloc(sizeof(char) * (ft_len(s, start, len) + 1));
	if (!ptr)
		return (NULL);
	while (i < ft_len(s, start, len) && ((unsigned char *)s)[start + i])
	{
		ptr[i] = ((unsigned char *)s)[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
int	main(void)
{
	char	*ptr;

	ptr = ft_substr("hola", -1, -1);
	printf("%s", ptr);
	free(ptr);
	return (0);
}*/
