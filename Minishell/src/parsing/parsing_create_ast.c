/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_ast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 13:44:33 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* create new node */
void	ft_new_ast_node(t_ast **node, t_ast_type type)
{
	*node = ft_calloc(1, sizeof(t_ast));
	if (!(*node))
		return ;
	(*node)->type = type;
}

/* create node for tree based on the type of node */

t_ast	*ft_create_ast_redirect(t_token_type direction, char *target)
{
	t_ast	*node;

	if (!target)
		return (ft_error_syntax("newline"), NULL);
	ft_new_ast_node(&node, AST_REDIRECT);
	if (node)
	{
		node->redirect = ft_calloc(1, sizeof(*node->redirect));
		if (!node->redirect)
			return (free(node), NULL);
		node->redirect->direction = direction;
		node->redirect->target = target;
		node->redirect->next = NULL;
	}
	return (node);
}

// check here cmd[0] need to be cmd!!!

t_ast	*ft_create_ast_words(char **args)
{
	t_ast	*node;
	
	ft_new_ast_node(&node, AST_WORDS);
	// printf("we pass here\n\n");
	// printf("node type ok: %i\n\n", node->type);
	if (node)
	{
		// printf("node exist\n\n");
		node->cmd_words = ft_calloc(1, sizeof(*node->cmd_words));
		if (!node->cmd_words)
			return (free(node), NULL);
	}
	node->cmd_words->args = args; //FAUL
	// printf("word: %s\n\n", node->cmd_words->args[0]);
	return (node);
}

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
		return (ft_error_input(-200), NULL); //need check
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
		return (ft_error_input(100), NULL);
	ft_new_ast_node(&node, AST_EXPRESSION);
	// printf("**Expression Created type: %i\n", node->type);
	if (node)
	{
		node->expression = ft_calloc(1, sizeof(*node->expression));
		if (!node->expression)
			return (free(node), NULL);
		if (parenthesis == true)
		{
			node->expression->parenthesis = true;
			node->expression->cmd_or_sub = expression;
			// printf("** Expression Created subshell type: %i\n", node->type);
		}
		else
		{
			node->expression->parenthesis = false;
			node->expression->cmd_or_sub = expression;
			// printf("** Expression Created command type: %i\n", node->type);
		}
	}
	return (node);
}

t_ast	*ft_create_ast_pipeexpr(t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (ft_error_input(TK_PIPE), NULL); // need check error value
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
		return (ft_error_input(TK_AND), NULL); // need check error value
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

