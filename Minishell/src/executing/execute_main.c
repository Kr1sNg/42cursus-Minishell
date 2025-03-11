/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 16:11:27 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"
#include "../../include/libraries.h"
/* execute parsing - Recursive descent parser  */

int	ft_execute(t_ast *ast, t_env *env)
{
	int	status;
	
	status = EXIT_FAILURE;
	if (!ast)
		return (status);
	if (ast->type == AST_LOGICAL)
		status = ft_exe_logical(ast->logical, env);
	else if (ast->type == AST_PIPEEXPR)
	 	status = ft_exe_pipeexpr(ast->pipeexpr, env);
	else if	(ast->type == AST_EXPRESSION)
		status = ft_exe_expression(ast->expression, env);
	else if (ast->type == AST_SUBSHELL)
		status = ft_exe_subshell(ast->subshell, env);
	else if (ast->type == AST_COMMAND)
		status = ft_exe_command(ast->command, env);
	else if (ast->type == AST_WORDS)
		status = ft_exe_words(ast->cmd_words, env);
	else if (ast->type == AST_REDIRECT)
		status = ft_exe_redirect(ast, env);
	return (status);
}

int	ft_exe_logical(t_ast_logical *ast, t_env *env)
{
	int left_status;
	int	right_status;
	
	left_status = ft_execute(ast->left, env);
	if (ast->operator == TK_AND)
	{
		if (left_status == EXIT_SUCCESS)
		{
			right_status = ft_execute(ast->right, env);
			return (right_status);
		}
		return (left_status);
	}
	else if (ast->operator == TK_OR)
	{
		if (left_status != EXIT_SUCCESS)
		{
			right_status = ft_execute(ast->right, env);
			return (right_status);
		}
		return (left_status);
	}
	return (EXIT_FAILURE);
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

int ft_exe_expression(t_ast_expression *ast, t_env *env)
{
	return (ft_execute(ast->cmd_or_sub, env));
}

int ft_exe_subshell(t_ast_subshell *ast, t_env *env)
{
	int		status;
	pid_t	pid;
	t_ast	*redir;

	status = EXIT_FAILURE;
	redir = NULL;
	if (ast->redirect_list)
		redir = ast->redirect_list;
	while(redir)
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
		status = ft_execute(ast->logical, env);
		exit(status);
	}
	ft_close_io(env);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int ft_exe_command(t_ast_command *ast, t_env *env)
{
	int 	status;
	pid_t	pid;
	t_ast	*redir;

	status = EXIT_FAILURE;
	redir = NULL;
	if (!ast->redirect_list)
		return (ft_execute(ast->cmd_words, env)); // have to keep this for cd!
	if (ast->redirect_list)
		redir = ast->redirect_list;
	while (redir)
	{
		if (ft_exe_redirect(redir, env) == EXIT_FAILURE)
			return (ft_close_io(env), status);
		redir = redir->redirect->next;
	}
	if (!ft_strcmp(ast->cmd_words->cmd_words->args[0], "exit"))
		return(ft_exit(env));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
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
		status = ft_execute(ast->cmd_words, env);
		exit(status);
	}
	ft_close_io(env);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_exe_words(t_ast_words *ast, t_env *env)
{
	int status;

	status = EXIT_FAILURE;
	if (ast->args)
		status = ft_exec_cmd(ast->args, env);
	return (status);
}

