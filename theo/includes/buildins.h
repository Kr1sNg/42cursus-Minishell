/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:59:06 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/23 22:13:07 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

typedef struct s_init
{
	int	i;
	int	j;
	int	k;
	int	l;
}				t_init;

typedef struct s_infos
{
	char **env;
	char **export;
	char **list_export;
}				t_infos;

void	cmd_create_env(t_infos *infos, char **env);
void	cmd_create_export(t_infos *infos);
void	ft_exec_export(t_infos *infos, char **cmd);
void	ft_exec_env(char **env);
void	ft_exec_pwd(void);
void	ft_exec_cd(char *str, t_infos *infos);

int		ft_strlen_name_env(char *str);
int		check_egal(char *cmd);
char	**cmd_env_unset(char **env, char *cmd);
char	**cmd_add_env(char **env, char *cmd);
char	**cmd_add_export(char **env, char *cmd);
void	cmd_export(t_infos *infos, char *cmd);
void	cmd_unset(t_infos *infos, char *cmd);
void	free_tab(char **tab);
char	*convert_line_export(char *line);
char	**ft_print_sort_env(char **env);
char	**ft_sort_a(char **env);
char	*check_list_export(char *cmd, char **list);
int		ft_valide_export_cmd(char *cmd);
int		check_egal(char *cmd);
void	ft_swap(char **str, char **str2);

#endif
