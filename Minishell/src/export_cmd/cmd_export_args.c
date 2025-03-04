/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:29:34 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/03 21:09:23 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

int	check_egal(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

int	ft_valide_export_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
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
