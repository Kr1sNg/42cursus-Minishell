/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 16:40:52 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_exit(char **cmd, t_env *infos)
{
	long	i;

	i = EXIT_FAILURE;
	if (cmd && cmd[0] && cmd[1])
	{
		if (!ft_isdigit_s(cmd[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			i = 2;
		}
		else
		{
			if (cmd[2])
				return (printf("minishell: exit: too many arguments\n"), i);
			i = ft_atol(cmd[1]);
		}
	}
	else
		i = infos->status;
	ft_close_io(infos);
	ft_free_cmd(infos);
	free_tab(infos->env);
	free_tab(infos->export);
	exit(i);
}

int	ft_strcmp_exit(char *s)
{
	if (!ft_strncmp(s, "\'exit\'", -1))
		return (0);
	else if (!ft_strncmp(s, "\"exit\"", -1))
		return (0);
	else if (!ft_strncmp(s, "exit", -1))
		return (0);
	else
		return (1);		
}
