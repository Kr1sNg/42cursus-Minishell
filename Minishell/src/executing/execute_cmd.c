/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/17 22:30:27 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_exe_words(t_ast_words *ast, t_env *env)
{
	int	status;

	status = EXIT_FAILURE;
	if (ast->args)
		status = ft_exec_cmd(ast->args, env);
	return (status);
}

static int	execute_redirects(t_ast_command *ast, t_env *env)
{
	t_ast	*redir;

	redir = ast->redirect_list;
	while (redir)
	{
		if (ft_exe_redirect(redir, env) == EXIT_FAILURE)
		{
			ft_close_io(env);
			return (EXIT_FAILURE);
		}
		redir = redir->redirect->next;
	}
	return (EXIT_SUCCESS);
}

static void	exec_child_command(t_ast_command *ast, t_env *env, int *status)
{
	child_signals();
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
	*status = ft_execute(ast->cmd_words, env);
	free_tab(env->env);
	free_tab(env->export);
	ft_free_token(env->tokens);
	ft_free_ast(env->ast);
	exit(*status);
}

static int	exec_parent(pid_t pid, t_env *env, int *status)
{
	ignore_signals();
	ft_close_io(env);
	waitpid(pid, status, 0);
	return (WEXITSTATUS(*status));
}

int	ft_exe_command(t_ast_command *ast, t_env *env)
{
	int		status;
	pid_t	pid;

	status = EXIT_FAILURE;
	if (execute_redirects(ast, env) == EXIT_FAILURE)
		return (status);
	if (ft_check_buildins_out_echo(ft_cvt_cmd_on(
				ast->cmd_words->cmd_words->args[0])))
		return (ft_exec_cmd(ast->cmd_words->cmd_words->args, env));
	pid = fork();
	if (pid == -1)
		return (status);
	if (pid == 0)
		exec_child_command(ast, env, &status);
	return (exec_parent(pid, env, &status));
}

/*
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
	if (ft_check_buildins_out_echo(ft_cvt_cmd_on(
			ast->cmd_words->cmd_words->args[0])))
		return(ft_exec_cmd(ast->cmd_words->cmd_words->args, env));
	pid = fork();
	if (pid == -1)
		return (status);
	if (pid == 0)
	{
		child_signals();
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
	ignore_signals();
	ft_close_io(env);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
*/
