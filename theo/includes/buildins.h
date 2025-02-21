/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:59:06 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/21 01:41:53 by tbahin           ###   ########.fr       */
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
}				t_infos;

int		ft_strlen_name_env(char *str);
void	cmd_env(char **env);
char	**cmd_env_unset(char **env, char *cmd);
char	**cmd_env_export(char **env, char *cmd);
char	**cmd_create_env(char **env);
char	**cmd_export(char **env, char *cmd);
char	**cmd_unset(char **env, char *cmd);
void	cmd_pwd(void);
void	cmd_cd(char *str);

#endif
