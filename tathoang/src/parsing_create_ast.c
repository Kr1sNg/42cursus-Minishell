/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_ast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/25 21:11:54 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* create new node */
void	ft_new_ast_node(t_ast **node, t_ast_type type)
{
	*node = ft_calloc(1, sizeof(t_ast));
	if (!(*node))
		return NULL;
	(*node)->type = type;
}

/* create node for tree based on the type of node */

t_ast	*ft_create_ast_words(char **args)
{
	t_ast	*node;

	ft_new_ast_node(&node, AST_WORDS);
	node->u_ast_data.cmd_words.args = args;
	return (node);
}

t_ast	*ft_create_ast_redirection(t_token_type direction, t_token *tk_filename, t_ast *child)
{
	t_ast	*node;

	if (!tk_filename || tk_filename->type != TK_WORD)
		return (ft_error_input(TK_REDIR_IN), NULL); //need check error value
	ft_new_ast_node(&node, AST_REDIRECT);
	node->t_ast_data.redirect.direction = direction;
	node->t_ast_data.redirect.filename = tk_filename;
	node->t_ast_data.redirect.child = child;
	return (node);
}

t_ast *ft_create_ast_pipeline(t_ast *left, t_ast *right) 
{
	t_ast	*node;

	if (!left || !right)
		return (ft_error_input(TK_PIPE), NULL); // need check error value
	ft_new_ast_node(&node, AST_PIPELINE);
	node->u_ast_data.pipeline.left = left;
	node->u_ast_data.pipeline.right = right;
	return (node);
}

t_ast	*ft_create_ast_logical(t_token_type logical, t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (ft_error_input(TK_AND), NULL); // need check error value
	ft_new_ast_node(&node, AST_LOGICAL);
	node->u_ast_data.logical.logical = logical;
	node->u_ast_data.logical.left = left;
	node->u_ast_data.logical.right = right;
	return (node);
}

t_ast	*ft_create_ast_expression(t_ast *child)
{
	t_ast	*node;

	if (!child)
		return (ft_error_input(-200), NULL); //need check
	ft_new_ast_node(&node, AST_EXPRESSION);
	node->u_ast_data.expression.logical = child;
	return (node);
}
