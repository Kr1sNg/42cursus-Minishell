/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:12:41 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/18 17:20:04 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_error_tm_args(void)
{
	write(2, "minishell: cd: too many arguments\n", 35);
	return (1);
}

int	ft_exec_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	return (1);
}

void	ft_exec_cd_export(t_env *infos)
{
	char	*line;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	line = ft_strjoin("PWD=", pwd);
	cmd_export(infos, line);
	free(pwd);
	free(line);
}

int	ft_cd_no_args(int *error, t_env *infos)
{
	char	*tmp;

	tmp = NULL;
	tmp = value_env("HOME", infos);
	if (!tmp)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	else
	{
		*error = chdir(tmp);
		ft_exec_cd_export(infos);
		free(tmp);
		return (0);
	}
}

int	ft_exec_cd(char **cmd, t_env *infos)
{
	char	*acces;
	int		error;

	error = 0;
	if (!cmd[1])
	{
		if (ft_cd_no_args(&error, infos))
			return (1);
	}
	else
	{
		if (cmd[2])
			return (ft_error_tm_args());
		error = chdir(cmd[1]);
		ft_exec_cd_export(infos);
	}
	if (error == -1)
	{
		acces = ft_strjoin("minishell: cd: ", cmd[1]);
		perror(acces);
		free(acces);
		return (1);
	}
	return (0);
}
