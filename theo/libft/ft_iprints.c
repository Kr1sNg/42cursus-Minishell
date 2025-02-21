/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iprints.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:15:45 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/16 21:35:29 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_iprints(int fd, int nb)
{
	char	*number;
	size_t	len;

	number = ft_itoa(nb);
	ft_putstr_fd(number, fd);
	len = ft_strlen(number);
	free(number);
	return (len);
}
