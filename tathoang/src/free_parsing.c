/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/26 20:28:38 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// [...] means None or once
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

/*



            | 
        && ||        wc -l
    ls      pwd

[(ls && pwd)] | (wc -l)
[ls] && [pwd[]

*/