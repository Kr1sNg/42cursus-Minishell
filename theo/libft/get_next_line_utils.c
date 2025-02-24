/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:17:54 by tbahin            #+#    #+#             */
/*   Updated: 2025/01/08 16:05:21 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (ft_strlen_gnl(str) + 1));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_check_gnl(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (i + 1);
		i++;
	}
	if (line[0] == '\0')
		return (0);
	return (-1);
}

char	*ft_strcpy_gnl(char *line, char *dest)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
		{
			dest[i] = line[i];
			i++;
			break ;
		}
		dest[i] = line[i];
		i++;
	}
	dest[i] = '\0';
	if (line[i] != '\0')
	{
		str = ft_strdup(&line[i]);
		free(line);
		return (str);
	}
	free(line);
	return (NULL);
}

int	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcat_gnl(char *src, char *line, int lens, int lenl)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (lens + lenl + 1));
	if (!str)
	{
		free(line);
		return (NULL);
	}
	while (i < lenl)
	{
		str[i] = line[i];
		i++;
	}
	i = 0;
	while (src[i] && i < lens)
	{
		str[lenl + i] = src[i];
		i++;
	}
	str[lenl + i] = '\0';
	free(src);
	free(line);
	return (str);
}
