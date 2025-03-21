/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 09:30:38 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 20:38:45 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_exe_redirect(t_ast *ast, t_env *env)
{
	if (!ast || ast->type != AST_REDIRECT)
		return (EXIT_FAILURE);
	if (ast->redirect->direction == TK_REDIR_IN)
		env->fd_in = ft_open(ast->redirect->target, READ);
	else if (ast->redirect->direction == TK_REDIR_OUT)
		env->fd_out = ft_open(ast->redirect->target, WRITE);
	else if (ast->redirect->direction == TK_APPEND_OUT)
		env->fd_out = ft_open(ast->redirect->target, APPEND);
	else if (ast->redirect->direction == TK_HEREDOC)
		env->fd_in = ft_here_doc(ast->redirect->target);
	if (env->fd_in == -1 || env->fd_out == -1)
		return (ft_error_target(ast->redirect->target), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_close_io(t_env *env)
{
	if (env->fd_in != STDIN_FILENO && env->fd_in > -1)
		close(env->fd_in);
	if (env->fd_out != STDOUT_FILENO && env->fd_in > -1)
		close(env->fd_out);
}
