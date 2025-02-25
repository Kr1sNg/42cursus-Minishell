/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/25 15:47:38 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// [...] means None or once
// {...} means Zero or more times

<COMMAND_LINE>    	::= <LOGICAL>
<LOGICAL>       	::= <PIPELINE> { ("&&" | "||") <PIPELINE> } 
<PIPELINE>       	::= <EXPRESSION> { "|" <EXPRESSION> }
<EXPRESSION>     	::= <COMMAND> 
                    | "(" <LOGICAL> ")"
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

