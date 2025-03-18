/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:34:11 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/18 17:16:27 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_check_valid_export(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || cmd[0] == '\0')
		return (1);
	if (ft_isdigit(cmd[0]))
		return (1);
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	**cmd_add_export(char **env, char *cmd)
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
	env_cpy[i] = convert_line_export(cmd);
	env_cpy[i + 1] = NULL;
	return (env_cpy);
}

int	check_export_var(char *cmd, t_env *infos)
{
	int		i;
	char	*line;
	int		check;

	i = 0;
	check = 0;
	while (infos->export[i])
	{
		if (ft_strncmp(cmd, &infos->export[i][11], ft_strlen_egal(cmd)) == 0)
		{
			if (!check_egal(cmd))
			{
				line = infos->export[i];
				infos->export[i] = convert_line_export(cmd);
				if (ft_strncmp(cmd, "PWD", ft_strlen_egal("PWD")) == 0)
					check_list_var(ft_strjoin("OLD", line), infos, 1);
				free(line);
			}
			check = 1;
		}
		i++;
	}
	return (check);
}

int	check_list_var(char *cmd, t_env *infos, int free_old)
{
	int		check;

	check = 0;
	check += check_env_var(cmd, infos);
	check += check_export_var(cmd, infos);
	if (free_old == 1)
		free(cmd);
	return (check);
}
