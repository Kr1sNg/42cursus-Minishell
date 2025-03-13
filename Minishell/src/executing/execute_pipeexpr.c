/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeexpr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 20:36:49 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int ft_exe_expression(t_ast_expression *ast, t_env *env)
{
	return (ft_execute(ast->cmd_or_sub, env));
}

int	ft_exe_pipeexpr(t_ast_pipeexpr *ast, t_env *env)
{
	int status;
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	status = EXIT_FAILURE;
	if (pipe(fd) == -1)
		return (status);
	pid_left = fork();
	if (pid_left == -1)
		return (status);
	if (pid_left == 0)
	{
		if (ast->left)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			status = ft_execute(ast->left, env);
			close(fd[1]);
		}
		exit(status);
	}
	pid_right = fork();
	if (pid_right == -1)
		return (status);
	if (pid_right == 0)
	{
		if (ast->right)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			status = ft_execute(ast->right, env);
			close(fd[0]);
		}
		exit(status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	return (WEXITSTATUS(status));
}



