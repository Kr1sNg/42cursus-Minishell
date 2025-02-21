/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:54:36 by tbahin            #+#    #+#             */
/*   Updated: 2024/11/14 15:59:57 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_copy(char *s, char **dest, size_t len, int count)
{
	size_t	i;

	i = 0;
	dest[count] = malloc(sizeof(char) * (len + 1));
	if (!dest[count])
	{
		count--;
		while (count >= 0)
		{
			if (dest[count])
				free(dest[count]);
			count--;
		}
		free (dest);
		return (1);
	}
	while (s[i] && i < len)
	{
		dest[count][i] = s[i];
		i++;
	}
	dest[count][i] = '\0';
	return (0);
}

static size_t	ft_words(char const *s, char c, char **dest, int check)
{
	size_t	i;
	int		count;
	size_t	temp;

	i = 0;
	count = 0;
	temp = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		temp = i;
		while (s[i] != c && s[i])
			i++;
		if (check == 1)
		{
			if (ft_copy(((char *)s) + temp, dest, i - temp, count) == 1)
				break ;
		}
		count++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	count;

	ptr = NULL;
	count = ft_words(s, c, ptr, 0);
	ptr = malloc((count + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	if (count != 0)
	{
		if (ft_words(s, c, ptr, 1) != count)
			return (NULL);
	}
	ptr[count] = NULL;
	return (ptr);
}
/*
int	main(void)
{
	char	**tabstr;
	size_t	i;

	tabstr = NULL;
	i = 0;
	if (!(tabstr = ft_split("", 'z')))
        	printf("NULL");
    	else
    	{
        	if (!tabstr[0])
        	{
            		printf("OK\n");
            		i++;
        	}
    	}
	if (tabstr)
		free(tabstr);
	return (0);
}*/
