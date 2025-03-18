/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:32:39 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/18 17:16:06 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

char	**cmd_add_env(char **env, char *cmd)
{
	char	**env_cpy;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (env[i])
		i++;
	env_cpy = (char **)malloc((i + 2) * sizeof(int *));
	while (j < i)
	{
		env_cpy[j] = (char *)malloc((ft_strlen(env[j]) + 1) * sizeof(char));
		k = 0;
		while (env[j][k])
		{
			env_cpy[j][k] = env[j][k];
			k++;
		}
		env_cpy[j++][k] = '\0';
	}
	env_cpy[i] = ft_strdup(cmd);
	env_cpy[i + 1] = NULL;
	return (env_cpy);
}

int	check_env_var(char *cmd, t_env *infos)
{
	int		i;
	char	*line;
	int		check;

	check = 0;
	i = 0;
	while (infos->env[i])
	{
		if (infos->env[i]
			&& ft_strncmp(cmd, infos->env[i], ft_strlen_egal(cmd)) == 0)
		{
			line = infos->env[i];
			infos->env[i] = ft_strdup(cmd);
			if (ft_strncmp(cmd, "PWD", ft_strlen_egal("PWD")) == 0)
				check_list_var(ft_strjoin("OLD", line), infos, 1);
			free(line);
			check = 1;
		}
		i++;
	}
	return (check);
}
