/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:56:55 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/17 18:16:57 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_exec_execve(char **cmd, char **env)
{
	if (access(cmd[0], F_OK | X_OK) == 0)
		return (ft_manage_pipe_withpath(cmd, env));
	else
		return (ft_manage_pipe(cmd, env));
}

int	ft_exec_buildins(char **cmd, t_env *infos)
{
	char	*cpy;

	cpy = ft_cvt_cmd_on(cmd[0]);
	if (ft_strncmp(cpy, "echo", ft_strlen("echo0")) == 0)
		return (free(cpy), ft_exec_echo(cmd, infos));
	else if (ft_strncmp(cpy, "export", ft_strlen("export0")) == 0)
		return (free(cpy), ft_exec_export(ft_convert_cmd(cmd, infos), infos));
	else if (ft_strncmp(cpy, "unset", ft_strlen("unset0")) == 0)
		return (free(cpy), ft_exec_unset(ft_convert_cmd(cmd, infos), infos));
	else if (ft_strncmp(cpy, "env", ft_strlen("env0")) == 0)
		return (free(cpy), ft_exec_env(ft_convert_cmd(cmd, infos), infos->env));
	else if (ft_strncmp(cpy, "cd", ft_strlen("cd0")) == 0)
		return (free(cpy), ft_exec_cd(ft_convert_cmd(cmd, infos), infos));
	else if (ft_strncmp(cpy, "pwd", ft_strlen("pwd0")) == 0)
		return (free(cpy), ft_exec_pwd());
	else if (ft_strncmp(cpy, "exit", ft_strlen("exit0")) == 0)
		return (free(cpy), ft_exit(ft_convert_cmd(cmd, infos), infos));
	free(cpy);
	return (127);
}

int	ft_exec_cmd(char **cmd, t_env *infos)
{
	int		type_cmd;
	char	**cmd_dup;
	int		status;
	char	*cmd_name;

	cmd_dup = ft_check_wildcards(cmd, infos);
	cmd_name = ft_cvt_cmd_on(cmd_dup[0]);
	type_cmd = ft_check_valide_cmd(cmd_name, *infos);
	if (type_cmd == 0)
	{
		printf("%s: command not found\n", cmd_name);
		free_tab(cmd_dup);
		free(cmd_name);
		return (127);
	}
	free(cmd_name);
	if (type_cmd == 1)
		status = ft_exec_buildins(cmd_dup, infos);
	if (type_cmd == 2)
		status = ft_exec_execve(ft_convert_cmd(cmd_dup, infos), infos->env);
	free_tab(cmd_dup);
	return (status);
}
