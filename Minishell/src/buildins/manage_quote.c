/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:39:22 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/10 22:27:30 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

char	*ft_quote_clear(char *str)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	i = 1;
	j = 0;
	len = ft_strlen(str) - 2;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i + 1])
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	free(str);
	return(dest);
}

char	**ft_convert_cmd(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i][0] == '\"' || str[i][0] == '\'')
			str[i] = ft_quote_clear(str[i]);
		i++;
	}
	return (str);
}