/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_export_only.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:29:39 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/17 18:05:59 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

char	*var_export_only_quote(int check, char *dest, int i, char *line)
{
	if (check == 0 && line[i - 1] == '=')
	{
		dest[i++] = '\"';
		check++;
	}
	if (check == 1)
		dest[i] = '\"';
	dest[i + check] = '\0';
	return (dest);
}

char	*var_export_only(char *line)
{
	char	*dest;
	int		i;
	int		check;

	i = 0;
	check = 0;
	dest = malloc((ft_strlen(line) + 3) * sizeof(char));
	while (line[i - check])
	{
		if (check == 0 && i > 0 && line[i - 1] == '=')
		{
			dest[i] = '\"';
			check = 1;
		}
		else
			dest[i] = line[i - check];
		i++;
	}
	var_export_only_quote(check, dest, i, line);
	return (dest);
}
