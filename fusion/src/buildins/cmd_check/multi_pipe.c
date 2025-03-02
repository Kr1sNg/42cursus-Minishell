/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:31:19 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/02 10:37:25 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/buildins.h"

void	ft_child(char **cmd, char **env)
{
	char	*path;

	path = ft_getenv(cmd[0], env);
	if (!path)
	{
		perror("error path");
		exit(127);
	}
	if (execve(path, cmd, env) != 0)
	{
		free(path);
		ft_free_tab(cmd);
		perror("error exec");
		exit(127);
	}
}

void	ft_manage_pipe(char **cmd, char **env)
{
	pid_t	pid;
	// int		fd[2];

	// pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		// close(fd[0]);
		// dup2(fd[1], 1);
		ft_child(cmd, env);
	}
	else
	{
		// close(fd[1]);
		// dup2(fd[0], 0);
		wait(NULL);
	}
}
