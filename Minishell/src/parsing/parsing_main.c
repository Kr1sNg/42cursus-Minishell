/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 20:02:49 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* PARSING GRAMMAR
// [...] means Zero or once
// {...} means Zero or more times

<COMMAND_LINE>    	::= <LOGICAL>
<LOGICAL>       	::= <PIPEEXPR> { ("&&" | "||") <PIPEEXPR> } 
<PIPEEXPR>       	::= <EXPRESSION> { "|" <EXPRESSION> }
<EXPRESSION>     	::= <COMMAND>
					| <SUBSHELL>
					
<COMMAND>         	::= [ <REDIR_LIST> ] <CMD_WORDS> [ <REDIR_LIST> ]
<SUBSHELL>          ::= "(" <LOGICAL> ")" [ <REDIR_LIST> ]

<CMD_WORDS>       	::= <WORD> { <WORD> }
<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }

<REDIRECTION>     	::= (">" | "<" | ">>") <WORD>
					| "<<" <WORD>
<WORD>				::= <WORD>
*/

/* start to convert tokens list into an abstract syntax tree */

/* <COMMAND_LINE>    	::= <LOGICAL> */
// if (token) -> for verify if there's extra token after command line

t_ast	*ft_parse(t_token *token)
{
	t_ast	*ast;

	if (token && (token->type == TK_AND || token->type == TK_OR
			|| token->type == TK_PIPE))
		return (ft_error_syntax(token->word), NULL);
	ast = ft_parse_logical(&token);
	if (token)
	{
		if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT
			|| token->type == TK_APPEND_OUT || token->type == TK_HEREDOC)
			ft_error_syntax("newline");
		else
			ft_error_syntax(token->word);
		return (ft_free_ast(ast), NULL);
	}
	return (ast);
}

/*<LOGICAL>       	::= <PIPELINE> { ("&&" | "||") <PIPELINE> }*/

t_ast	*ft_parse_logical(t_token **token)
{
	t_token_type	operator;
	t_ast			*left;
	t_ast			*right;
	char			c;

	left = ft_parse_pipeexpr(token);
	while ((*token) && ((*token)->type == TK_AND || (*token)->type == TK_OR))
	{
		c = (*token)->word[0];
		operator = (*token)->type;
		*token = (*token)->next;
		right = ft_parse_pipeexpr(token);
		if (!right)
		{
			ft_free_ast(left);
			if (c == '|')
				return (ft_error_syntax("||"), NULL);
			else
				return (ft_error_syntax("&&"), NULL);
		}
		left = ft_create_ast_logical(operator, left, right);
	}
	return (left);
}

/*<PIPEEXPR>       	::= <EXPRESSION> { "|" <EXPRESSION> }*/

t_ast	*ft_parse_pipeexpr(t_token **token)
{
	t_ast	*left;
	t_ast	*right;

	left = ft_parse_expression(token);
	right = NULL;
	while (*token && (*token)->type == TK_PIPE)
	{
		*token = (*token)->next;
		if (!(*token))
		{
			ft_free_ast(left);
			return (ft_error_syntax("|"), NULL);
		}
		right = ft_parse_expression(token);
		left = ft_create_ast_pipeexpr(left, right);
	}
	return (left);
}

/*<EXPRESSION> ::= <COMMAND>
//             | "(" <LOGICAL> ")" [ <REDIR_LIST> ] */

t_ast	*ft_parse_expression(t_token **token)
{
	t_ast	*expression;

	if (*token && (*token)->type == TK_SUBSHELL_OPEN)
	{
		expression = ft_parse_subshell(token);
		return (ft_create_ast_expression(expression, true));
	}
	else
	{
		expression = ft_parse_command(token);
		return (ft_create_ast_expression(expression, false));
	}
	return (ft_error_syntax("("), NULL);
}
