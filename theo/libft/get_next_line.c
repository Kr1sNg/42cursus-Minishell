/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:29:46 by tbahin            #+#    #+#             */
/*   Updated: 2025/01/08 16:03:38 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, int *nb_read, char **line)
{
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	*nb_read = read(fd, buf, BUFFER_SIZE);
	if (*nb_read == -1 || (*nb_read == 0 && !*line))
	{
		if (*line)
		{
			free(*line);
			*line = NULL;
		}
		free(buf);
		return (NULL);
	}
	buf[*nb_read] = '\0';
	return (buf);
}

char	*ft_alloc(char **line, int nb, int check, char *buf)
{
	char	*dest;

	dest = malloc(sizeof(char) * (nb));
	if (!dest)
		return (NULL);
	*line = ft_strcpy_gnl(*line, dest);
	if (check == 1)
		free (buf);
	else
		(void)buf;
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*dest;
	int			nb_read;
	char		*buf;

	nb_read = -1;
	buf = NULL;
	if (ft_check_gnl(line) != (-1))
	{
		dest = ft_alloc(&line, ft_check_gnl(line) + 1, 0, buf);
		return (dest);
	}
	buf = ft_read(fd, &nb_read, &line);
	if (!buf)
		return (NULL);
	if (nb_read == 0 && line)
	{
		dest = ft_alloc(&line, ft_strlen_gnl(line) + 1, 1, buf);
		return (dest);
	}
	line = ft_strcat_gnl(buf, line, nb_read, ft_strlen_gnl(line));
	dest = get_next_line(fd);
	return (dest);
}
