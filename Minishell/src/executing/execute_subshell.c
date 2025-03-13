/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 20:39:09 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

static void	dup2_close(t_env *env)
{
	if (env->fd_in != STDIN_FILENO)
	{
		dup2(env->fd_in, STDIN_FILENO);
		close(env->fd_in);
	}
	if (env->fd_out != STDOUT_FILENO)
	{
		dup2(env->fd_out, STDOUT_FILENO);
		close(env->fd_out);
	}
}

int	ft_exe_subshell(t_ast_subshell *ast, t_env *env)
{
	int		status;
	pid_t	pid;
	t_ast	*redir;

	status = EXIT_FAILURE;
	redir = NULL;
	if (ast->redirect_list)
		redir = ast->redirect_list;
	while (redir)
	{
		if (ft_exe_redirect(redir, env) == EXIT_FAILURE)
			return (ft_close_io(env), status);
		redir = redir->redirect->next;
	}
	pid = fork();
	if (pid == -1)
		return (status);
	if (pid == 0)
	{
		dup2_close(env);
		status = ft_execute(ast->logical, env);
		exit(status);
	}
	ft_close_io(env);
	return (waitpid(pid, &status, 0), WEXITSTATUS(status));
}
