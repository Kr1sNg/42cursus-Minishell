/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:31:54 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/14 14:43:44 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_open(char *name, int read_write)
{
	int	fd;

	fd = -1;
	if (read_write == READ)
		fd = open(name, O_RDONLY, 0777);
	else if (read_write == WRITE)
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (read_write == APPEND)
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	return (fd);
}

char	*ft_findname(char *name)
{
	int		i;
	char	*real_name;

	i = 0;
	real_name = NULL;
	while (name[i] != ' ' && name[i] != '\0')
		i++;
	real_name = malloc((i + 1) * sizeof(char));
	if (!real_name)
	{
		perror("failed malloc");
		exit(1);
	}
	i = 0;
	while (name[i] != ' ' && name[i] != '\0')
	{
		real_name[i] = name[i];
		i++;
	}
	real_name[i] = '\0';
	return (real_name);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
