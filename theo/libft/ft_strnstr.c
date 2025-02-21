/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:17:54 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/11 20:00:42 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!little[j])
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i] == little[j] && i < len)
		{
			i++;
			j++;
			if (!little[j])
				return (&((char *)big)[i - j]);
		}
		i -= j;
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	printf("%s", ft_strnstr("aaabcabcd","aabc", -1));
	return (0);
}*/
