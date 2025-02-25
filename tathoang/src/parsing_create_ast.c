/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/24 13:06:05 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// [...] means None or once
// {...} means Zero or more times

<COMMAND_LINE>      ::= <LOGICAL_EXPR>
<LOGICAL_EXPR>    	::= <PIPE_EXPR> { ("&&" | "||") <PIPE_EXPR> } 
<PIPE_EXPR>       	::= <SIMPLE_EXPR> { "|" <SIMPLE_EXPR> }
<SIMPLE_EXPR>     	::= <COMMAND> 
                    | "(" <LOGICAL_EXPR> ")"
<COMMAND>         	::= <CMD_WORDS> [ <REDIR_LIST> ]
<CMD_WORDS>       	::= <WORD> { <WORD> }
                    | <ASSIGNMENT_WORD> { <WORD> }
<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }
<REDIRECTION>     	::= (">" | "<" | ">>") <FILENAME>
                    | "<<" <HERE_END>
<ASSIGNMENT_WORD>	::= <WORD> "=" <WORD>
<FILENAME>			::= <WORD>
<HERE_END>			::= <WORD>
<WORD>				::= <WORD>
```
*/

/* create new node */
void	ft_new_ast_node(t_ast **node, t_ast_type type)
{
	*node = ft_calloc(1, sizeof(t_ast));
	if (!(*node))
		return NULL;
	(*node)->type = type;
}

/* create node for tree based on the type of node */
t_ast	*ft_create_ast_cmd(char	**argv)
{
	t_ast	*node;

	ft_new_ast_node(&node, AST_CMD);
	node->t_ast_data.cmd.args = argv;  // why?
	return (node);
}

t_ast *ft_create_ast_subshell(t_ast *child)
{
	t_ast	*node;

	if (!child)
		return (ft_error_input(TK_SUBSHELL_OPEN), NULL); // error need to check
	ft_new_ast_node(&node, AST_SUBSHELL);
	node->t_ast_data.subshell.child = child;
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
	ft_new_ast_node(&node, AST_PIPE);
	node->t_ast_data.pipeline.left = left;
	node->t_ast_data.pipeline.right = right;
	return (node);
}

t_ast	*ft_create_ast_logical(t_token_type operator, t_ast *left, t_ast *right)
{
	t_ast	*node;

	if (!left || !right)
		return (ft_error_input(TK_AND), NULL); // need check error value
	ft_new_ast_node(&node, AST_LOGICAL);
	node->t_ast_data.logical.logical = operator;
	node->t_ast_data.logical.left = left;
	node->t_ast_data.logical.right = right;
	return (node);
}
