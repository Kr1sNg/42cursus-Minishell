/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:32:11 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/21 01:40:41 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildins.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_infos	infos;

	infos.env = cmd_create_env(env);
	cmd_env(infos.env);
	infos.env = cmd_export(infos.env, "test");
	cmd_env(infos.env);
	infos.env = cmd_unset(infos.env, "test");
	cmd_env(infos.env);
    return (0);
}