/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:29:34 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/22 22:01:03 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/buildins.h"

int		ft_valide_export_cmd(char *cmd)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		if (cmd[i] > 32 && cmd[i] <= 126)
			return (0);
		i++;
	}
	return (1);
}

char	*check_list_export(char *cmd, char **list)
{
	int	i;

	i = 0;
	if (!list)
		return (ft_strdup(cmd));
	while (list[i])
	{
		if (ft_strcmp(list[i], cmd) == 61)
		{
			return (ft_strdup(list[i]));
		}
		i++;
	}
	return (ft_strdup(cmd));
}