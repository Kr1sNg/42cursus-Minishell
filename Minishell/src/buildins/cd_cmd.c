/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:12:41 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/03 16:55:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

void	ft_exec_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	free(pwd);
}

void	ft_exec_cd(char **cmd, t_env *infos)
{
	char	*line;
	char	*pwd;
	char	*user;
	char	*acces;

	if (!cmd[1])
	{
		user = value_env("USER", infos);
		acces = ft_strjoin("/home/", user);
		chdir(acces);
		free(acces);
	}
	else
		chdir(cmd[1]);
	pwd = getcwd(NULL, 0);
	line = ft_strjoin("PWD=",pwd );
	cmd_export(infos, line);
	free(pwd);
	free(line);
}