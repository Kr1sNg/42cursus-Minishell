/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:31:19 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/17 18:14:26 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

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

int	ft_manage_pipe_withpath(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd[0], cmd, env) != 0)
		{
			ft_free_tab(cmd);
			perror("error exec");
			exit(127);
		}
	}
	else
	{
		wait(&status);
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	ft_manage_pipe(char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_child(cmd, env);
	}
	else
	{
		wait(&status);
		return (WEXITSTATUS(status));
	}
	return (0);
}
