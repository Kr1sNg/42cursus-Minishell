/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:46:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/12 13:35:45 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

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
			write(2, "minishell: export: `", 20);
			ft_putstr_fd(cmd[i], 2);
			write(2, "\': not a valid identifier\n", 26);
			return(1);
		}
		cmd_export(infos, cmd[i]);
		i++;
	}
	return (0);
}
