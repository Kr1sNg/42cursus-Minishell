/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valide_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:36:36 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/18 11:56:54 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_check_buildins_out_echo(char *cmd)
{
	int	res;

	res = 0;
	if (ft_strncmp(cmd, "pwd", ft_strlen("pwd0")) == 0)
		res = 1;
	else if (ft_strncmp(cmd, "export", ft_strlen("export0")) == 0)
		res = 1;
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset0")) == 0)
		res = 1;
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd0")) == 0)
		res = 1;
	else if (ft_strncmp(cmd, "env", ft_strlen("env0")) == 0)
		res = 1;
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit0")) == 0)
		res = 1;
	free(cmd);
	return (res);
}

int	ft_check_buildins(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen("echo0")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd0")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", ft_strlen("export0")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset0")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd0")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", ft_strlen("env0")) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit0")) == 0)
		return (1);
	return (0);
}
