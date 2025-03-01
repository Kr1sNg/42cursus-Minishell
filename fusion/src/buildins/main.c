/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:32:11 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/01 17:59:13 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

int	main(int ac, char **av, char **env)
{
	t_env	infos;
	char	*cmd;

	cmd = NULL;
	if (ac > 1)
		infos.list_export = &av[1];
	else
		infos.list_export = NULL;
	cmd_create_env(&infos, env);
	cmd_create_export(&infos);
	ft_exec_env(infos.env);
	cmd_export(&infos, NULL);;
	cmd_export(&infos, "test");
	ft_exec_env(infos.env);
	cmd_export(&infos, NULL);
	cmd_unset(&infos, "test");
	ft_exec_env(infos.env);
	cmd_export(&infos, NULL);
	free_tab(infos.export);
	free_tab(infos.env);
	return (0);
}
