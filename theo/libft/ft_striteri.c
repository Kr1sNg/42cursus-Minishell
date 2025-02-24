/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:04:56 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/10 16:21:04 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
/*
void	ft_toupperbis(unsigned int index, char *c)
{
	if (*c >= 'a' && *c <= 'z' && index % 2 == 0)
		*c -= 32;
}
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(f)(i, &s[i]);
		i++;
	}
}
/*
int	main(void)
{
	char	str[] = "Lorem ipsum dolor sit amet.";
	
	ft_striteri(str, &ft_toupperbis);
	printf("%s", str);
	return (0);
}*/
