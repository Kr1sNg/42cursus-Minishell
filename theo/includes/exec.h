/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:58:38 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/23 13:35:45 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXEC_H
# define EXEC_H

#include "../libft/libft.h"
#include "buildins.h"
#include "pipex.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	ft_check_valide_cmd(char *cmd, t_infos infos);
void	ft_manage_pipe(char **cmd, char **env);
void	ft_child(char **cmd, char **env);

#endif