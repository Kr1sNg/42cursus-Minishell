/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:46:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/09 17:39:57 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

int	ft_check_valid_export(char *cmd)
{
	int	i;

	i = 0;
	if (ft_isdigit(cmd[0]))
		return(1);
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return(1);
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
int	check_env_var(char *cmd, t_env *infos)
{
	int		i;
	char	*line;
	int		check;

	check = 0;
	i = 0;
	while (infos->env[i])
	{
		if (infos->env[i] && ft_strncmp(cmd, infos->env[i], ft_strlen_egal(cmd)) == 0)
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
	return(check);
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

void	cmd_export_no_args(t_env *infos)
{
	ft_sort_a(infos->export);
	ft_display_export(infos->export);
}

void	cmd_export(t_env *infos, char *cmd)
{
	char	**env_cpy;
	char	*cpy_cmd;
	int		check;

	env_cpy = NULL;
	if (!cmd)
		cmd_export_no_args(infos);
	else
	{
		cpy_cmd = ft_strdup(cmd);
		check = check_list_var(cpy_cmd, infos, 0);
		if (check_egal(cpy_cmd) == 0 && check != 2)
		{
			env_cpy = cmd_add_env(infos->env, cpy_cmd);
			free_tab(infos->env);
			infos->env = env_cpy;
		}
		if (check == 0)
		{
			env_cpy = cmd_add_export(infos->export, cpy_cmd);
			free_tab(infos->export);
			infos->export = env_cpy;
		}
		free(cpy_cmd);
	}
}

void	cmd_create_export(t_env *infos)
{
	infos->export = ft_print_sort_env(infos->env);
}

int	ft_exec_export(char **cmd, t_env *infos)
{
	int	i;
	
	i = 1;
	if (!cmd[1])
		cmd_export(infos, NULL);
	while(cmd[i])
	{
		if (ft_check_valid_export(cmd[i]))
		{
			write(2, "bash: export: `", 15);
			ft_putstr_fd(cmd[i], 2);
			write(2, "\': not a valid identifier\n", 26);
			return(1);
		}
		cmd_export(infos, cmd[i]);
		i++;
	}
	return (0);
}
