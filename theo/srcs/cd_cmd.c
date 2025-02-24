/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 19:12:41 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/23 22:14:47 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/buildins.h"

void	ft_exec_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s\n", pwd);
	free(pwd);
}

void	ft_exec_cd(char *str, t_infos *infos)
{
	char	*line;
	char	*pwd;

	chdir(str);
	pwd = getcwd(NULL, 0);
	line = ft_strjoin("PWD=",pwd );
	cmd_export(infos, line);
	free(pwd);
	free(line);
}