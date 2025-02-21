/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/20 21:12:32 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

/*	
	OPERATION, //|, ||, && 1
	REDIRECT, // >, <, >>, << 2
	QUOTE, // " ", ' ' 3
	TEXT, BUILTIN, OPTION // -n, text, echo, cd, pwd, export, unset, env, exit 0
*/


int	ft_token_type(char *s)
{
	if (*s == '|' || *s == '&')
		return (OPERATION);
	else if (*s == '>' || *s == '<')
		return (REDIRECT);
	else if (*s == '\'' || *s == '\"')
		return (QUOTE);
	else
		return (TEXT);
}

