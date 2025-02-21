/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:32:11 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/21 13:57:43 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildins.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_infos	infos;

	infos.env = cmd_create_env(env);
	cmd_export(infos.env, NULL);
    return (0);
}