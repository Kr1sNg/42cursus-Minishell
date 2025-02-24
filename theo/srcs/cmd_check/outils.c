/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:31:54 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/18 21:43:55 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

int	ft_open(char *name, int read_write)
{
	int	fd;

	fd = 0;
	if (read_write == 0)
		fd = open(name, O_RDONLY, 0777);
	if (read_write == 1)
		fd = open(name, O_WRONLY | O_CREAT, 0777);
	if (read_write == 2)
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
