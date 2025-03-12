/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:56:55 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/12 21:12:57 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_exec_execve(char **cmd, char **env)
{
	return(ft_manage_pipe(cmd, env));
}

int	ft_exec_buildins(char **cmd, t_env *infos)
{
	if (ft_strncmp(ft_convert_cmd(cmd)[0], "echo", ft_strlen("echo0")) == 0)
		return(ft_exec_echo(cmd, infos));
	if (ft_strncmp(ft_convert_cmd(cmd)[0], "export", ft_strlen("export0")) == 0)
		return(ft_exec_export(cmd, infos));
	if (ft_strncmp(ft_convert_cmd(cmd)[0], "unset", ft_strlen("unset0")) == 0)
		return(ft_exec_unset(cmd, infos));
	if (ft_strncmp(ft_convert_cmd(cmd)[0], "env", ft_strlen("env0")) == 0)
		return(ft_exec_env(cmd, infos->env));
	if (ft_strncmp(ft_convert_cmd(cmd)[0], "cd", ft_strlen("cd0")) == 0)
		return(ft_exec_cd(cmd, infos));
	if (ft_strncmp(ft_convert_cmd(cmd)[0], "pwd", ft_strlen("pwd0")) == 0)
		return(ft_exec_pwd());
	if (ft_strncmp(ft_convert_cmd(cmd)[0], "exit", ft_strlen("exit0")) == 0)
		return(ft_exit(cmd, infos));
	return(127);
}

int	ft_exec_cmd(char **cmd, t_env *infos)
{
	int		type_cmd;

	cmd = ft_check_wildcards(cmd, infos);
	type_cmd = ft_check_valide_cmd(ft_convert_cmd_only(cmd[0]), *infos);
	if (type_cmd == 0)
	{
		printf("%s: command not found\n", cmd[0]);
		return (127);
	}
	if (type_cmd == 1)
		return(ft_exec_buildins(cmd, infos));
	if (type_cmd == 2)
		return(ft_exec_execve(ft_convert_cmd(cmd), infos->env));
	return(127);
}