/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_strdup_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:29:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 22:22:57 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* these functions are to split command line into tokens */

static int	count_letter_quote(char *s, char c)
{
	int	i;

	i = 0;
	c = s[i++];
	while (s[i] && s[i] != c)
		i++;
	i++;
	return (i);
}

static int	count_letter(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] && is_operator(&str[i]) == 1)
		return (1);
	else if (str[i] && is_operator(&str[i]) > 1)
		return (2);
	else if (str[i] && is_quote(str[i]))
		return(count_letter_quote(&str[i], str[i]));
	else
	{
		while ((str[i] != '\0') && !ft_isspace(str[i])
			&& !is_quote(str[i]) && !is_operator(&str[i]))
			i++;
	}
	return (i);
}

char	*ft_strdup_s(char *src)
{
	int		i;
	int		len;
	char	*arr;

	i = 0;
	len = count_letter(src);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
