/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:32:11 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/22 22:04:14 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildins.h"

int main(int ac, char **av, char **env)
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
	cmd = ft_strdup("test");
	cmd_export(&infos, cmd);
	free(cmd);
	cmd = ft_strdup("one");
	cmd_export(&infos, cmd);
	free(cmd);
	cmd = ft_strdup("t");
	cmd_export(&infos, cmd);
	free(cmd);
	cmd = ft_strdup("t");
	cmd_unset(&infos, cmd);
	free(cmd);
	cmd_export(&infos, NULL);
	printf("\n\n");
	cmd_env(infos.env);
	free_tab(infos.export);
	free_tab(infos.env);
    return (0);
}
