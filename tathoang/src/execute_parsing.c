/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/26 21:40:52 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* execute parsing - Recursive descent parser  */

int	ft_execute(t_ast *ast)
{
	int	status;

	if (!ast)
		return (EXIT_FAILURE);
	// if (ast->type == AST_COMMAND || ast->type == AST_REDIRECT)
	// 	printf("AST_CMD or AST_REDIRECT\n");
	if (ast->type == AST_LOGICAL)
		status = ft_exe_logical(&ast->u_ast_data.logical);
	else if (ast->type == AST_PIPEEXPR)
	 	status = ft_exe_pipeexpr(&ast->u_ast_data.pipeexpr);
	else if (ast->type == AST_SUBSHELL)
		status = ft_exe_subshell(&ast->u_ast_data.subshell);
	else if (ast->type == AST_COMMAND)
		status = ft_exe_command(&ast->u_ast_data.command);
	else if (ast->type == AST_WORDS)
		status = ft_exe_words(&ast->u_ast_data.cmd_words);
	else if (ast->type == AST_REDIRECT)
		status = ft_exe_redirect(&ast->u_ast_data.redirect);
	else
	{
		status = -42;
		printf("Error execute!\n");
	}
	return (status);
}

int	ft_exe_logical(t_ast_logical *ast)
{
	int left_status;
	int	right_status;
	
	printf("1 - LOGICAL LEVEL\n"); //
	left_status = ft_execute(ast->left);
	printf("1-left of logical\n"); //
	if (ast->logical == TK_AND)
	{
		printf("1-logical AND &&\n"); //
		if (left_status == EXIT_SUCCESS)
		{
			printf("1-right of AND &&\n");//
			right_status = ft_execute(ast->right);
			return (right_status);
		}
		return (left_status);
	}
	else if (ast->logical == TK_OR)
	{
		printf("1-logical OR ||\n"); //
		if (left_status != EXIT_SUCCESS)
		{
			printf("1-right of OR ||\n"); //
			right_status = ft_execute(ast->right);
			return (right_status);
		}
		return (left_status);
	}
	return (EXIT_FAILURE);
}

int	ft_exe_pipeexpr(t_ast_pipeexpr *ast)
{
	int left_status;
	int	right_status;

	printf("2 - PIPEEXPR level\n");
	if (ast->left)
	{
		printf("2-pipe Left\n");
		left_status = ft_execute(ast->left);
	}
	if (ast->right)
	{
		printf("2-pipe Right\n");
		right_status = ft_execute(ast->right);
	}
	return (EXIT_SUCCESS);
}

int ft_exe_subshell(t_ast_subshell *ast)
{
	int	status;

	printf("3 EXPRESSION LEVEL - option A: (SUBSHELL)\n");
	if (ast->logical)
	{
		printf("3a subshell - logical\n");
		status = ft_execute(ast->logical);
	}	
	if (ast->redirect_list)
	{
		printf("3a subshell - redirect_list\n");
		status = ft_execute(ast->redirect_list);
	}
	return (EXIT_SUCCESS);
}

int ft_exe_command(t_ast_command *ast)
{
	int status;
	printf("3 EXPRESSION LEVEL - option B: COMMAND\n");
	if (ast->cmd_words)
	{
		printf("3b-cmd_words\n");
		status = ft_execute(ast->cmd_words);
	}
	if (ast->redirect_list)
	{
		printf("3b-redirect list\n");
		status = ft_execute(ast->redirect_list);
	}
	return (EXIT_SUCCESS);
}

int	ft_exe_words(t_ast_words *ast)
{
	printf("4 - WORDS LEVEL\n");
	if (ast->args)
	{
		printf("4-real_command: {%s}\n", ast->args[0]);
	}
	return (EXIT_SUCCESS);
}

int	ft_exe_redirect(t_ast_redirect *ast)
{
	printf("5 - REDIRECT LEVEL\n");
	if (ast->direction)
	{
		printf("5-target_file: {%s}\n", ast->target);
	}
	return (EXIT_FAILURE);
}

