/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:06:40 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/08 11:06:08 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

/*
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	lend;
	size_t	lens;

	i = 0;
	lend = ft_strlen(dst);
	lens = ft_strlen(src);
	if (size <= lend)
		return (size + lens);
	while (src[i] && (lend + i < size - 1))
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = '\0';
	return (lend + lens);
}
/*
int	main(void)
{
	char		dst[20] = "Hello";
	const char	*src = "42";
	size_t		len;
	
	len = ft_strlcat(dst, src, 12);
	printf("%s || %zu", dst, len);
	return (0);
}*/
