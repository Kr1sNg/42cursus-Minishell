/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:32:11 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/23 22:39:16 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildins.h"

int	main(int ac, char **av, char **env)
{
	t_infos	infos;
	char	*cmd;

	cmd = NULL;
	if (ac > 1)
		infos.list_export = &av[1];
	else
		infos.list_export = NULL;
	cmd_create_env(&infos, env);
	cmd_create_export(&infos);
	ft_exec_env(infos.env);
	cmd_export(&infos, NULL);
	ft_exec_pwd();
	ft_exec_cd("../../..", &infos);
	ft_exec_env(infos.env);
	cmd_export(&infos, NULL);
	ft_exec_pwd();
	free_tab(infos.export);
	free_tab(infos.env);
	return (0);
}
