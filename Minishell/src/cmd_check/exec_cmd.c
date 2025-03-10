/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:56:55 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/10 08:29:12 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

int	ft_exec_execve(char **cmd, char **env)
{
	return(ft_manage_pipe(cmd, env));
}

int	ft_exec_buildins(char **cmd, t_env *infos)
{
	if (ft_strncmp(cmd[0], "echo", ft_strlen("echo0")) == 0)
		return(ft_exec_echo(cmd, infos));
	if (ft_strncmp(cmd[0], "export", ft_strlen("export0")) == 0)
		return(ft_exec_export(cmd, infos));
	if (ft_strncmp(cmd[0], "unset", ft_strlen("unset0")) == 0)
		return(ft_exec_unset(cmd, infos));
	if (ft_strncmp(cmd[0], "env", ft_strlen("env0")) == 0)
		return(ft_exec_env(cmd, infos->env));
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd0")) == 0)
		return(ft_exec_cd(cmd, infos));
	if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd0")) == 0)
		return(ft_exec_pwd());
	if (ft_strncmp(cmd[0], "exit", ft_strlen("exit0")) == 0)
	{
		printf("exit\n");
		exit(0);
		return(1);
	}
		// return(ft_exit(0));
	// if (ft_strncmp(cmd[0], "true", ft_strlen("true0")) == 0)
	// 	return(ft_true_false("true"));
	// if (ft_strncmp(cmd[0], "false", ft_strlen("false0")) == 0)
	// 	return(ft_true_false("false"));
	return(127);
}

int	ft_exec_cmd(char **cmd, t_env *infos)
{
	int		type_cmd;
	// int	status;

	type_cmd = ft_check_valide_cmd(cmd[0], *infos);
	if (type_cmd == 0)
	{
		printf("%s: command not found\n", cmd[0]);
		return (127);
	}
	if (type_cmd == 1)
		return(ft_exec_buildins(cmd, infos));
	if (type_cmd == 2)
		return(ft_exec_execve(cmd, infos->env));
	return(127);
}
