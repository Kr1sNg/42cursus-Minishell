/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:12:41 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/09 13:00:54 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

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

int	ft_exec_cd(char **cmd, t_env *infos)
{
	char	*line;
	char	*pwd;
	char	*acces;
	int		error;

	if (!cmd[1])
	{
		acces = ft_strjoin("/home/", value_env("USER", infos));
		error = chdir(acces);
		free(acces);
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
	pwd = getcwd(NULL, 0);
	line = ft_strjoin("PWD=",pwd );
	cmd_export(infos, line);
	free(pwd);
	free(line);
	return (0);
}