/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:08:58 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/05 11:05:07 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echodouble(char *str, t_env *infos)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '$' && isalpha(str[i + 1]))
		{
			i++;
			ft_var_env(&str[i], infos);
			while (isalpha(str[i]))
				i++;
		}
		else if (str[i] != '\"')
		{
			printf("%c", str[i]);
			i++;
		}
		else
			i++;
	}
}

void	ft_echosimple(char *str, t_env *infos)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] != '\'')
		{
			printf("%c", str[i]);
			i++;
		}
		else
			i++;
	}
}

void	ft_exec_echo(char **cmd, t_env *infos)
{
	int	i;

	i = 1;
	if (ft_strncmp(cmd[1], "-n", ft_strlen("-n0")) == 0)
		i++;
	while(cmd[i])
	{
		if (cmd[i][0] == '\'')
			ft_echosimple(cmd[i], infos);
		else if (cmd[i][0] == '\"')
			ft_echodouble(cmd[i], infos);
		else
			ft_echodouble(cmd[i], infos);
		printf(" ");
		i++;
	}
	if (ft_strncmp(cmd[1], "-n", ft_strlen("-n0")) != 0)
		printf("\n");
	
}