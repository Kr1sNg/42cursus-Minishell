/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 22:19:10 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

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

int	is_operator(char *s)
{
	if ((s[0] == '|' || s[0] == '>' || s[0] == '<') && s[1])
	{
		if (s[1] == s[0])
			return (11);
		else if (s[1] && (ft_isalnum(s[1]) || ft_isspace(s[1])))
			return (1);
		else
			return (-42);
	}
	else if (s[0] == '(' || s[0] == ')')
		return (1);
	else if (s[0] == '&' && s[1])
	{
		if (s[1] == s[0])
			return (22);
		else
			return (-42);
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == '\"')
		return (34);
	else if (c == '\'')
		return (39);
	else
		return (0);
}
