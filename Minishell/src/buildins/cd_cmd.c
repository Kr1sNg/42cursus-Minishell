/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:12:41 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/02 01:36:00 by tbahin           ###   ########.fr       */
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

	if (!cmd[1])
		return ;
	chdir(cmd[1]);
	pwd = getcwd(NULL, 0);
	line = ft_strjoin("PWD=",pwd );
	cmd_export(infos, line);
	free(pwd);
	free(line);
}