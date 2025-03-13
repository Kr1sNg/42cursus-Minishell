/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:40 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/13 13:45:06 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	int		len;
	char	**dest;

	i = 0;
	len = ft_tablen(tab);
	dest = (char **)malloc(sizeof(char *) * (len + 1));
	while(tab[i])
	{
		dest[i] = ft_strdup(tab[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}