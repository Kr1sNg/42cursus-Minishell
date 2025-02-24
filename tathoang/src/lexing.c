/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/24 11:17:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	
	OPERATION, //|, ||, && 1
	REDIRECT, // >, <, >>, << 2
	QUOTE, // " ", ' ' 3
	TEXT, BUILTIN, OPTION // -n, text, echo, cd, pwd, export, unset, env, exit 0
*/


t_token_type	ft_token_type(char *word)
{
	if (*word == '(')
		return (TK_SUBSHELL_OPEN);
	else if (*word == ')')
		return (TK_SUBSHELL_CLOSE);
	else if (ft_strlen(word) == 2 && *word == '&')
		return (TK_AND);
	else if (ft_strlen(word) == 2 && *word == '|')
		return (TK_OR);
	else if (ft_strlen(word) == 1 && *word == '|')
		return (TK_PIPE);
	else if (ft_strlen(word) == 1 && *word == '<')
		return (TK_REDIR_IN);
	else if (ft_strlen(word) == 1 && *word == '>')
		return (TK_REDIR_OUT);
	else if (ft_strlen(word) == 2 && *word == '>')
		return (TK_APPEND_OUT);
	else if (ft_strlen(word) == 2 && *word == '<')
		return (TK_HEREDOC);
	else if (*word == '\"')
		return (TK_DQUOTE);
	else if (*word == '\'')
		return (TK_SQUOTE);
	else
		return (TK_WORD);
}

