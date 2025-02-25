/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/25 15:22:02 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* parsing support functions */

t_token *ft_next_token(t_parser *parser)
{
    static t_token eof;
    
    if (parser->index < parser->token_count)
        return (&parser->tokens[parser->index++]);
    eof.type = TK_EOF;
    eof.word = NULL;
    eof.next = NULL;
    return (&eof);
}

t_token *ft_peek_token(t_parser *parser)
{
    static t_token eof;
    
    if (parser->index < parser->token_count)
        return (&parser->tokens[parser->index]);
    eof.type = TK_EOF;
    eof.word = NULL;
    eof.next = NULL;
    return (&eof);
}