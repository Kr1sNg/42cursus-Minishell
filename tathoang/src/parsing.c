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


t_ast	*ft_create_ast_cmd(char	**argv)
{
	t_ast	*node;

	ft_new_ast_node(&node, AST_CMD);
	node->t_ast_data.cmd.args = argv;  // why?
	return (node);
}

t_tree *ft_parse_expr(t_token **head)
{
	return (ft_parse_logical_expr(head));
}

/* logical expr is a pipe expr optionally followed by
zero or more logical operators && || and another pipe expr */

t_tree	*ft_parse_logical_expr(t_token **head);
{
	t_tree	*node;
	t_tree	*left;
	t_tree	*right;
	t_token	*tmp;

	tmp = *head;
	left = ft_parse_pipe_expr(tmp);
	while (*tmp && tmp->type == OPERATOR)
	{
		tmp = head->next;
		right = ft_parse_pipe_expr(tmp);
		node = new_ast_node(NODE_AND || NODE_OR)




}


t_tree ft_parse_pipe(t_token **start, t_token *end) // return pointer to tree
{
	t_tree	*new_node;
	
	new_node = ft_parse_exec(start, end);
	if ()
	
}

int ft_parse_line(t_token *token);

int ft_parse_block(t_token *token)


/*
- differnt kinds of node: EXEC (non-terminal symbol), BLOCK, 

- parseblock read in '(' recursive call parseline, scan ')' and call parsedirs

*/
