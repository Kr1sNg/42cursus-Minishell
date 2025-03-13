/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 14:22:22 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_exe_words(t_ast_words *ast, t_env *env)
{
	int status;

	status = EXIT_FAILURE;
	if (ast->args)
		status = ft_exec_cmd(ast->args, env);
	return (status);
}

int ft_exe_command(t_ast_command *ast, t_env *env)
{
	int 	status;
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
	if (ft_check_buildins_out_echo(ast->cmd_words->cmd_words->args[0]))
		return(ft_exec_cmd(ast->cmd_words->cmd_words->args, env));
	pid = fork();
	if (pid == -1)
		return (status);
	if (pid == 0)
	{
		restore_default_signals();
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
		status = ft_execute(ast->cmd_words, env);
		exit(status);
	}
	else
	{
		ignore_signals();
		ft_close_io(env);
		waitpid(pid, &status, 0);
		setup_signal_handlers();
	}
	return (WEXITSTATUS(status));
}


