/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:12:13 by theo              #+#    #+#             */
/*   Updated: 2025/03/09 13:04:49 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

char	*value_env(char *name, t_env *infos)
{
	int		i;
	char	*line;

	i = 0;
	while (infos->env[i])
	{
		if (ft_strncmp(infos->env[i], name, ft_strlen_egal(name)) == 0)
		{
			line = strdup(infos->env[i]);
			while(*line != '=')
				line++;
			line++;
			return (line);
		}
		i++;
	}
	return (NULL);
}

int	ft_limite(char str)
{
	if (str == 32 || (str >= 9 && str <= 13) || str == '\'' || str == '\"')
		return (1);
	else if (!str)
		return (1);
	return (0);
}

void	ft_var_env(char *str, t_env *infos)
{
	int	len;
	char	*name;
	char	*value;

	value = NULL;
	len = 0;
	while (!ft_limite(str[len]))
		len++;
	name = (char *)malloc((len + 1) * sizeof(char));
	name[len] = '\0';
	len--;
	while(len >= 0)
	{
		name[len] = str[len];
		len--;
	}
	value = value_env(name, infos);
	if (value)
	{
		printf("%s", value);
	}
	free(name);
}

int	ft_exec_env(char **cmd, char **env)
{
	int	i;

	i = 0;
	if (cmd[1])
		return (127);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
