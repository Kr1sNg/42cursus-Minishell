/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/01 21:12:00 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/* execute parsing - Recursive descent parser  */

int	ft_execute(t_ast *ast, t_env *env)
{
	int	status;
	
	status = EXIT_SUCCESS;
	if (!ast)
		return (EXIT_FAILURE);
	// if (ast->type == AST_WORDS || ast->type == AST_REDIRECT)
	// 	printf("AST_CMD or AST_REDIRECT\n");
	if (ast->type == AST_LOGICAL)
		status = ft_exe_logical(&ast->u_ast_data.logical, env);
	else if (ast->type == AST_PIPEEXPR)
	 	status = ft_exe_pipeexpr(&ast->u_ast_data.pipeexpr, env);
	else if	(ast->type == AST_EXPRESSION)
		status = ft_exe_expression(&ast->u_ast_data.expression, env);
	else if (ast->type == AST_SUBSHELL)
		status = ft_exe_subshell(&ast->u_ast_data.subshell, env);
	else if (ast->type == AST_COMMAND)
		status = ft_exe_command(&ast->u_ast_data.command, env);
	else if (ast->type == AST_WORDS)
		status = ft_exe_words(&ast->u_ast_data.cmd_words, env);
	else if (ast->type == AST_REDIRECT)
		status = ft_exe_redirect(ast);
	// else
	// {
	// 	status = -42;
	// 	printf("Error execute!\n");
	// }
	return (status);
}

int	ft_exe_logical(t_ast_logical *ast, t_env *env)
{
	int left_status;
	int	right_status;
	
	printf("1 - LOGICAL LEVEL\n"); //
	printf(" 1-left of logical\n"); //
	left_status = ft_execute(ast->left, env);
	if (ast->logical == TK_AND)
	{
		printf(" 1- AND &&\n"); //
		if (left_status == EXIT_SUCCESS)
		{
			printf(" 1-right of AND\n");//
			right_status = ft_execute(ast->right, env);
			return (right_status);
		}
		return (left_status);
	}
	else if (ast->logical == TK_OR)
	{
		printf(" 1- OR ||\n"); //
		if (left_status != EXIT_SUCCESS)
		{
			printf(" 1-right of OR\n"); //
			right_status = ft_execute(ast->right, env);
			return (right_status);
		}
		return (left_status);
	}
	return (EXIT_FAILURE);
}

int	ft_exe_pipeexpr(t_ast_pipeexpr *ast, t_env *env)
{
	int left_status;
	int	right_status;

	printf("\t2 - PIPEEXPR level\n");
	if (ast->left)
	{
		printf("\t 2-pipe Left\n");
		left_status = ft_execute(ast->left, env);
	}
	if (ast->right)
	{
		printf("\t 2-pipe Right\n");
		right_status = ft_execute(ast->right, env);
	}
	return (EXIT_SUCCESS);
}

int ft_exe_expression(t_ast_expression *ast, t_env *env)
{
	int	status;

	printf("\t\t3- EXPRESSION LEVEL\n");
	if (ast->parenthesis)
		status = ft_execute(ast->subshell, env);
	else
		status = ft_execute(ast->command, env);
	return (EXIT_SUCCESS);
}

int ft_exe_subshell(t_ast_subshell *ast, t_env *env)
{
	int	status;

	printf("\t\t 3-option A: (SUBSHELL)\n");
	if (ast->logical)
	{
		printf("\t\t 3a subshell - logical\n");
		status = ft_execute(ast->logical, env);
	}	
	if (ast->redirect_list)
	{
		printf("\t\t 3a subshell - redirect_list\n");
		status = ft_execute(ast->redirect_list, env);
	}
	return (EXIT_SUCCESS);
}

int ft_exe_command(t_ast_command *ast, t_env *env)
{
	int status;
	printf("\t\t 3-option B: COMMAND\n");
	if (ast->cmd_words)
	{
		printf("\t\t 3b-cmd_words\n");
		status = ft_execute(ast->cmd_words, env);
	}
	if (ast->redirect_list)
	{
		printf("\t\t 3b-redirect list\n");
		status = ft_execute(ast->redirect_list, env);
	}
	return (EXIT_SUCCESS);
}

int	ft_exe_words(t_ast_words *ast, t_env *env)
{
	int i = 0;
	printf("\t\t\t4 - WORDS LEVEL\n");
	if (ast->args)
	{
		printf("\t\t\t 4-builtin {%s}\n", ast->args[i++]);
		while (ast->args[i])
			printf("\t\t\t 4-text: {%s}\n", ast->args[i++]);
		ft_exec_cmd(ast->args, env);
	}
	return (EXIT_SUCCESS);
}

int	ft_exe_redirect(t_ast *ast)
{
	printf("\t\t\t\t5 - REDIRECT LEVEL\n");
	if (ast)
	{
		while (ast)
		{
			printf("\t\t\t\t 5-target_file: {%s}\n", ast->u_ast_data.redirect.target);
			ast = ast->u_ast_data.redirect.next;
		}
	}
	return (EXIT_SUCCESS);
}

