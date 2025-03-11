/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 18:59:16 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* create node for tree based on the type of node */

t_ast	*ft_create_ast_command(t_ast *ahead, t_ast *cmd_words, t_ast *behind)
{
	t_ast	*node;
	t_ast	*redir_list;

	redir_list = NULL;
	ft_redir_list_add(&redir_list, ahead);
	ft_redir_list_add(&redir_list, behind);
	ft_new_ast_node(&node, AST_COMMAND);
	if (node)
	{
		node->command = ft_calloc(1, sizeof(*node->command));
		if (!node->command)
			return (free(node), NULL);
		node->command->cmd_words = cmd_words;
		node->command->redirect_list = redir_list;
	}
	return (node);
}

t_ast	*ft_create_ast_subshell(t_ast *logical, t_ast *redir_list)
{
	t_ast	*node;

	if (!logical)
		return (NULL);
	ft_new_ast_node(&node, AST_SUBSHELL);
	if (node)
	{
		node->subshell = ft_calloc(1, sizeof(*node->subshell));
		if (!node->subshell)
			return (free(node), NULL);
		node->subshell->logical = logical;
		node->subshell->redirect_list = redir_list;
	}
	return (node);
}

t_ast	*ft_create_ast_expression(t_ast *expression, bool parenthesis)
{
	t_ast	*node;

	if (!expression)
		return (NULL);
	ft_new_ast_node(&node, AST_EXPRESSION);
	if (node)
	{
		node->expression = ft_calloc(1, sizeof(*node->expression));
		if (!node->expression)
			return (free(node), NULL);
		if (parenthesis == true)
		{
			node->expression->parenthesis = true;
			node->expression->cmd_or_sub = expression;
		}
		else
		{
			node->expression->parenthesis = false;
			node->expression->cmd_or_sub = expression;
		}
	}
	return (node);
}

t_ast	*ft_create_ast_pipeexpr(t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (NULL);
	ft_new_ast_node(&node, AST_PIPEEXPR);
	if (node)
	{
		node->pipeexpr = ft_calloc(1, sizeof(*node->pipeexpr));
		if (!node->pipeexpr)
			return (free(node), NULL);
		node->pipeexpr->left = left;
		node->pipeexpr->right = right;
	}
	return (node);
}

t_ast	*ft_create_ast_logical(t_token_type operator, t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (NULL);
	ft_new_ast_node(&node, AST_LOGICAL);
	if (node)
	{
		node->logical = ft_calloc(1, sizeof(*node->logical));
		if (!node->logical)
			return (free(node), NULL);
	}
	node->logical->operator = operator;
	node->logical->left = left;
	node->logical->right = right;
	return (node);
}
