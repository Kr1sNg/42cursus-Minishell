/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:46:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/22 22:03:23 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/buildins.h"


int		check_egal(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (0);
		i++;
	}
	return (1);
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
		while(env[j][k])
		{
			env_cpy[j][k] = env[j][k];
			k++;
		}
		env_cpy[j][k] = '\0';
		j++;
	}
	env_cpy[i] = convert_line_export(cmd);
	env_cpy[i + 1] = NULL;
	return (env_cpy);
}

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
		while(env[j][k])
		{
			env_cpy[j][k] = env[j][k];
			k++;
		}
		env_cpy[j][k] = '\0';
		j++;
	}
	env_cpy[i] = ft_strcpy(env_cpy[i], cmd, ft_strlen(cmd));
	env_cpy[i + 1] = NULL;
	return (env_cpy);
}

void	cmd_export(t_infos *infos, char *cmd)
{
	char	**env_cpy;
	char	*cpy_cmd;

	env_cpy = NULL;
	if (!cmd)
	{
		ft_sort_a(infos->export);
		cmd_env(infos->export);
	}
	else if (ft_valide_export_cmd(cmd) == 1)
		return ;
	else
	{
		cpy_cmd = check_list_export(cmd, infos->list_export);
		if (check_egal(cpy_cmd) == 0)
		{
			env_cpy = cmd_add_env(infos->env, cpy_cmd);
			free_tab(infos->env);
			infos->env = env_cpy;
		}
		env_cpy =  cmd_add_export(infos->export, cpy_cmd);
		free_tab(infos->export);
		infos->export = env_cpy;
		free(cpy_cmd);
	}
}

void	cmd_create_export(t_infos *infos)
{
	infos->export = ft_print_sort_env(infos->env);
}
