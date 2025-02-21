/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uprints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:27:05 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/16 21:36:56 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(unsigned int number)
{
	char			*nb;
	int				count;
	unsigned int	copy;

	nb = NULL;
	count = 0;
	copy = number;
	while (copy != 0)
	{
		copy /= 10;
		count++;
	}
	nb = malloc(sizeof(char) * (count + 1));
	if (!nb)
		return (NULL);
	nb[count] = '\0';
	count--;
	while (count >= 0)
	{
		nb[count] = number % 10 + 48;
		number /= 10;
		count--;
	}
	return (nb);
}

size_t	ft_uprints(int fd, unsigned int number)
{
	char	*ptr;
	size_t	len;

	if (number == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	ptr = ft_convert(number);
	if (!ptr)
		return (0);
	len = ft_strlen(ptr);
	ft_putstr_fd(ptr, fd);
	free(ptr);
	return (len);
}
