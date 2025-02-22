/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:36:50 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/22 18:54:26 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strcpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	dest = (char *)malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
int	main(void)
{
	const char	*src = "HELLO";
	char		dest[6];
	ft_strlcpy(dest, src, 6);
	printf("%s", dest);
	return (0);
}*/
