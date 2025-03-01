/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:09:17 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/01 18:01:08 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/buildins.h"

char	**cmd_env_unset(char **env, char *cmd)
{
	char	**env_cpy;
	t_init	index;

	index.l = 0;
	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (env[index.i])
		(index.i)++;
	env_cpy = (char **)malloc((index.i + 1) * sizeof(int *));
	while (index.j + index.l < index.i)
	{
		if (ft_strncmp(cmd, env[index.j + index.l],
				ft_strlen_name_env(env[index.j + index.l])) == 0)
			(index.l) = 1;
		if (index.j + index.l == index.i)
			break ;
		env_cpy[index.j] = (char *)malloc((ft_strlen(env[index.j
						+ index.l]) + 1) * sizeof(char));
		index.k = 0;
		while (env[index.j + index.l][index.k])
		{
			env_cpy[index.j][index.k] = env[index.j + index.l][index.k];
			(index.k)++;
		}
		env_cpy[index.j][index.k] = '\0';
		(index.j)++;
	}
	if (index.j + index.l < index.i)
		env_cpy[index.j] = NULL;
	env_cpy[index.j] = NULL;
	return (env_cpy);
}

void	cmd_unset(t_env *infos, char *cmd)
{
	char	**env_cpy;
	char	**export_cpy;
	char	*cpy_line;

	cpy_line = convert_line_export(cmd);
	env_cpy = NULL;
	export_cpy = NULL;
	env_cpy = cmd_env_unset(infos->env, cmd);
	free_tab(infos->env);
	infos->env = env_cpy;
	export_cpy = cmd_env_unset(infos->export, cpy_line);
	free(cpy_line);
	free_tab(infos->export);
	infos->export = export_cpy;
}

void	ft_exec_unset(char **cmd, t_env *infos)
{
	int	i;
	
	i = 1;
	if (!cmd[1])
		return ;
	while(cmd[i])
	{
		cmd_unset(infos, cmd[i]);
		i++;
	}
}
