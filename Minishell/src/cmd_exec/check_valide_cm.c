/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_cm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:36:36 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/18 11:57:19 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_check_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_ws(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_execve(char *cmd, char **env)
{
	char	*path;

	if (!cmd[0] || !ft_ws(cmd))
		return (0);
	path = ft_getenv(cmd, env);
	if (!path)
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			return (2);
		}
		else
			return (0);
	}
	free(path);
	return (2);
}

int	ft_check_valide_cmd(char *cmd, t_env infos)
{
	if (ft_check_buildins(cmd) == 1)
		return (1);
	if (ft_check_execve(cmd, infos.env) == 2)
		return (2);
	return (0);
}
