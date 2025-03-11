/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 19:05:46 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	ft_free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == AST_LOGICAL)
		ft_free_logical(ast);
	else if (ast->type == AST_PIPEEXPR)
		ft_free_pipeexpr(ast);
	else if (ast->type == AST_EXPRESSION)
		ft_free_expression(ast);
	else if (ast->type == AST_SUBSHELL)
		ft_free_subshell(ast);
	else if (ast->type == AST_COMMAND)
		ft_free_command(ast);
	else if (ast->type == AST_WORDS)
		ft_free_words(ast);
	else if (ast->type == AST_REDIRECT)
		ft_free_redir_list(ast);
	else
		free(ast);
}

void	ft_free_logical(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->logical->left)
		ft_free_ast(ast->logical->left);
	if (ast->logical->right)
		ft_free_ast(ast->logical->right);
	free(ast->logical);
	free(ast);
}

void	ft_free_pipeexpr(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->pipeexpr->left)
		ft_free_ast(ast->pipeexpr->left);
	if (ast->pipeexpr->right)
		ft_free_ast(ast->pipeexpr->right);
	free(ast->pipeexpr);
	free(ast);
}

void	ft_free_expression(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type)
		ft_free_ast(ast->expression->cmd_or_sub);
	free(ast->expression);
	free(ast);
}

void	ft_free_subshell(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->subshell->logical)
		ft_free_ast(ast->subshell->logical);
	if (ast->subshell->redirect_list)
		ft_free_ast(ast->subshell->redirect_list);
	free(ast->subshell);
	free(ast);
}
