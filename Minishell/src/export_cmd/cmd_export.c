/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:46:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/03 21:09:29 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

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
		while (env[j][k])
		{
			env_cpy[j][k] = env[j][k];
			k++;
		}
		env_cpy[j][k] = '\0';
		j++;
	}
	env_cpy[i] = ft_strdup(cmd);
	env_cpy[i + 1] = NULL;
	return (env_cpy);
}

int	check_env_var(char *cmd, t_env *infos, int free_old)
{
	int		i;
	char	*line;
	char	*oldline;
	int		check;

	i = 0;
	check = 0;
	while (infos->env[i])
	{
		if (ft_strncmp(cmd, infos->env[i], ft_strlen_egal(cmd)) == 0)
		{
			line = infos->env[i];
			infos->env[i] = ft_strdup(cmd);
			if (ft_strncmp(cmd, "PWD", ft_strlen_egal("PWD")) == 0)
			{
				oldline = ft_strjoin("OLD", line);
				check_env_var(oldline, infos, 1);
			}
			free(line);
			check = 1;
		}
		if (ft_strncmp(cmd, &infos->export[i][11], ft_strlen_egal(cmd)) == 0)
		{
			line = infos->export[i];
			infos->export[i] = ft_strjoin("declare -x ", cmd);
			if (ft_strncmp(cmd, "PWD", ft_strlen_egal("PWD")) == 0)
			{
				oldline = ft_strjoin("OLD", line);
				check_env_var(oldline, infos, 1);
			}
			free(line);
			check = 1;
		}
		i++;
	}
	if (free_old == 1)
		free(cmd);
	return (check);
}

void	cmd_export(t_env *infos, char *cmd)
{
	char	**env_cpy;
	char	*cpy_cmd;

	env_cpy = NULL;
	if (!cmd)
	{
		ft_sort_a(infos->export);
		ft_display_export(infos->export);
	}
	// else if (ft_valide_export_cmd(cmd) == 1)
	// 	return ;
	else
	{
		// printf("%s", infos->list_export);
		// cpy_cmd = check_list_export(cmd, infos->list_export);
		// printf("DEBUG");
		cpy_cmd = ft_strdup(cmd);
		if (check_env_var(cpy_cmd, infos, 0) == 1)
		{
			free(cpy_cmd);
			return ;
		}
		if (check_egal(cpy_cmd) == 0)
		{
			env_cpy = cmd_add_env(infos->env, cpy_cmd);
			free_tab(infos->env);
			infos->env = env_cpy;
		}
		env_cpy = cmd_add_export(infos->export, cpy_cmd);
		free_tab(infos->export);
		infos->export = env_cpy;
		free(cpy_cmd);
	}
}

void	cmd_create_export(t_env *infos)
{
	infos->export = ft_print_sort_env(infos->env);
}

void	ft_exec_export(char **cmd, t_env *infos)
{
	int	i;
	
	i = 1;
	if (!cmd[1])
		cmd_export(infos, NULL);
	while(cmd[i])
	{
		cmd_export(infos, cmd[i]);
		i++;
	}
}
