/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:36:36 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/03 21:08:59 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

int	ft_check_buildins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", ft_strlen("env")) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

int	ft_check_execve(char *cmd, char **env)
{
	char	*path;

	path = ft_getenv(cmd, env);
	if (!path)
		return (0);
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
