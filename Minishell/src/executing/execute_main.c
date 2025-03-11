/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 18:45:53 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (ast->type == AST_EXPRESSION)
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
	int	left_status;
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
