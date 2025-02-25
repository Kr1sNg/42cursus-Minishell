/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/24 12:56:43 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// [...] means None or once
// {...} means Zero or more times

<COMMAND_LINE>    	::= <LOGICAL_EXPR>
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

/* converts tokens list into an abstract syntax tree */

int	ft_parse(t_token *token_list, t_ast **ast)
{
    *ast = ft_parse_logical(token);
}