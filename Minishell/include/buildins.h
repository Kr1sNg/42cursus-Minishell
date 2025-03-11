/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:59:06 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/10 22:20:03 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include "../libft/includes/libft.h"
# include "minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_init
{
	int	i;
	int	j;
	int	k;
	int	l;
}	t_init;

typedef struct s_env
{
	char **env;
	char **export;
	char **list_export;
	int		status;
	int		fd_in;
	int		fd_out;
}	t_env;

typedef struct s_args
{
	char	*path;
	char	**cmd;
	char	**env;
}	t_args;

void	cmd_create_env(t_env *infos, char **env);
void	cmd_create_export(t_env *infos);
int		ft_exec_export(char **cmd, t_env *infos);
int		ft_exec_env(char **cmd, char **env);
int		ft_exec_pwd(void);
int		ft_exec_cd(char **cmd, t_env *infos);
int		ft_exec_unset(char **cmd, t_env *infos);
int		ft_exec_echo(char **cmd, t_env *infos);
void	ft_display_export(char **env);
int		ft_strlen_name_env(char *str);
int		check_egal(char *cmd);
char	**cmd_env_unset(char **env, char *cmd);
char	**cmd_add_env(char **env, char *cmd);
char	**cmd_add_export(char **env, char *cmd);
void	cmd_export(t_env *infos, char *cmd);
void	cmd_unset(t_env *infos, char *cmd);
void	free_tab(char **tab);
char	*convert_line_export(char *line);
char	**ft_print_sort_env(char **env);
char	**ft_sort_a(char **env);
char	*check_list_export(char *cmd, char **list);
int		ft_valide_export_cmd(char *cmd);
int		check_egal(char *cmd);
void	ft_swap(char **str, char **str2);
char	*var_export_only(char *line);

int		ft_check_valide_cmd(char *cmd, t_env infos);
void	ft_child(char **cmd, char **env);

int		check_env_var(char *cmd, t_env *infos);
char	*ft_getenv(char *name, char **env);
char	*ft_getpath(char *name, char **path);
char	*ft_strjoin_pipex(char const *s1, char const *s2, char *sep);
char	*ft_strcat_pipex(char *dest, char *src);
int		ft_open(char *name, int rw);
char	*ft_findname(char *name);
void	ft_free_tab(char **tab);
int		ft_manage_pipe(char **cmd, char **env);
void	ft_child(char **cmd, char **env);
int		ft_exec_cmd(char **cmd, t_env *infos);
char	*value_env(char *name, t_env *infos);
void	ft_var_env(char *str, t_env *infos);
int		check_list_var(char *cmd, t_env *infos, int free_old);
int		ft_check_valid_export(char *cmd);
char	**ft_convert_cmd(char **str);

// int		ft_true_false(char *t);

#endif
