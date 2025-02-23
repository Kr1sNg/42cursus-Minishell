/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:56:55 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/23 21:39:04 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/buildins.h"
#include "../../includes/exec.h"

void	ft_exec_execve(char **cmd, char **env)
{
	ft_manage_pipe(cmd, env);
}

void	ft_exec_buildins(char **cmd, t_infos *infos)
{
	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0)
		ft_exec_export(cmd, infos);
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		ft_exec_unset(cmd, infos);
	if (ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])) == 0)
		ft_exec_env(infos->env);
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		ft_exec_cd(cmd[0], infos);
	if (ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])) == 0)
		ft_exec_pwd();
}

void	ft_exec_cmd(char **cmd, t_infos *infos)
{
	int	type_cmd;

	type_cmd = ft_check_valide_cmd(cmd[0], *infos);
	if (type_cmd == 0)
		return ;
	if (type_cmd == 1)
		ft_exec_buildins(cmd, infos);
	if (type_cmd == 2)
		ft_exec_execve(cmd, infos->env);
}