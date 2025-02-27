/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create_ast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/27 12:22:45 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (ft_error_input(-300), NULL); //need check error value
	ft_new_ast_node(&node, AST_REDIRECT);
	node->u_ast_data.redirect.direction = direction;
	node->u_ast_data.redirect.target = target;
	node->u_ast_data.redirect.next = NULL;
	return (node);
}

// check here cmd[0] need to be cmd!!!

t_ast	*ft_create_ast_words(char **args)
{
	t_ast	*node;
	
	// if (!(*args)) // || check_cmd (args[0])
	// {
	// 	if (args[0])
	// 		ft_error_command(args[0]);
	// 	return (NULL);
	// }
	ft_new_ast_node(&node, AST_WORDS);
	node->u_ast_data.cmd_words.args = args;
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
	node->u_ast_data.command.cmd_words = cmd_words;
	node->u_ast_data.command.redirect_list = redir_list;
	return (node);
}

t_ast	*ft_create_ast_subshell(t_ast *logical, t_ast *redir_list)
{
	t_ast	*node;

	if (!logical)
		return (ft_error_input(-200), NULL); //need check
	ft_new_ast_node(&node, AST_SUBSHELL);
	node->u_ast_data.subshell.logical = logical;
	node->u_ast_data.subshell.redirect_list = redir_list;
	return (node);
}

t_ast	*ft_create_ast_pipeline(t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (ft_error_input(TK_PIPE), NULL); // need check error value
	ft_new_ast_node(&node, AST_PIPEEXPR);
	node->u_ast_data.pipeexpr.left = left;
	node->u_ast_data.pipeexpr.right = right;
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

