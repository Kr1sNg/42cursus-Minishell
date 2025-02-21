/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:02:08 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/11 19:19:27 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static void	ft_convert(long int n, char *s, size_t len)
{
	s[len] = '\0';
	if (n == 0)
		s[0] = '0';
	while (len > 0)
	{
		s[len - 1] = n % 10 + 48;
		n /= 10;
		len--;
	}
}

static size_t	ft_len(int n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n > 9 || n < -9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;

	str = NULL;
	len = ft_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		len--;
		ft_convert(-((long int)n), &str[1], len);
	}
	else
		ft_convert(n, str, len);
	return (str);
}
/*
int	main(void)
{
	int		nb;
	char	*str;

	nb = -2147483648;
	str = ft_itoa(nb);
	printf("%s", str);
	free(str);
	return (0);
}*/
