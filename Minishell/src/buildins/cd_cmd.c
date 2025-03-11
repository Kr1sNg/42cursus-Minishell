/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:12:41 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/11 13:44:18 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_error_tm_args(void)
{
	write(2, "bash: cd: Too many arguments\n", 29);
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
	line = ft_strjoin("PWD=",pwd );
	cmd_export(infos, line);
	free(pwd);
	free(line);
}

int	ft_exec_cd(char **cmd, t_env *infos)
{
	char	*acces;
	int		error;

	error = 0;
	if (!cmd[1])
	{
		if (!value_env("HOME", infos))
		{
			write(2, "bash: cd: HOME not set\n", 23);
			return (1);
		}
		else
			error = chdir(value_env("HOME", infos));
	}
	else
	{
		if (cmd[2])
			return(ft_error_tm_args());
		error = chdir(cmd[1]);
	}
	if (error == -1)
	{
		acces = ft_strjoin("bash: cd: ", cmd[1]);
		perror(acces);
		free(acces);
		return (1);
	}
	return (0);
}
