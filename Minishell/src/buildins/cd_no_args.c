/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_no_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:12:13 by theo              #+#    #+#             */
/*   Updated: 2025/03/03 16:26:07 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

char	*value_env(char *name, t_env *infos)
{
	int		i;
	char	*line;

	i = 0;
	while (infos->env[i])
	{
		if (ft_strncmp(infos->env[i], name, ft_strlen_egal(name)) == 0)
		{
			line = strdup(infos->env[i]);
			while(*line != '=')
				line++;
			line++;
			return (line);
		}
		i++;
	}
	return (NULL);
}