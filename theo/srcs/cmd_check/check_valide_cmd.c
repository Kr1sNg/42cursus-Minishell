/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:36:36 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/23 13:28:16 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/buildins.h"

int	ft_check_buildins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (1);
}

int	ft_check_execve(char **cmd, char **env)
{
	char	*path;

	path = ft_getenv(cmd[0], env);
	if (!path)
		return (0);
	free(path);
	return (2);
}

int	ft_check_valide_cmd(char *cmd, t_infos infos)
{
	int	check;

	check = 0;
	if (ft_check_buildins(cmd) == 1)
		return (check);
	if (ft_check_execve(cmd, infos.env) == 2)
		return (check);
	return (check);
}
