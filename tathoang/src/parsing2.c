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

/* converts tokens list into an abstract syntax tree */

/* converts all token TK_WORD into ast node AST_CMD */
t_ast	*ft_parse_cmd_word(t_token **token)
{
    t_token *current;
    int     argc;
    char    **argv;
    int     i;

    current = *token;
    argc = 0;
    while (current && current->type == TK_WORD)
    {
        argc++;
        current = current->next;
    }
    if (argc == 0)
        return (NULL);
    argv = ft_calloc((argc + 1), sizeof(char *));
    i = 0;
    while (i < argc)
    {
        argv[i++] = (*token)->word;
        *token = (*token)->next;
    }
    argv[argc] = NULL;
    return (ft_create_ast_cmd(argv));
}

t_ast   *ft_parse_cmd(t_token **token)
{
    t_token *current;



}

/* convert (all content inside parenthesis) into AST_SUBSHELL */

t_ast   *ft_parse_subshell(t_token **token)
{
    t_ast   *content;

    if (*token && (*token)->type == TK_SUBSHELL_OPEN)
    {
        *token = (*token)->next;
        content = ft_parse_logical(token);
        if 
    }
}

t_ast   *ft_parse_logical(t_token **token)
{
    t_token_type    logical;
    t_ast           *left;
    t_ast           *right;

    left = ft_parse_pipeline(token);

}

t_ast   *ft_parse_pipeline(t_token **token)
{
    t_ast   *left;
    t_ast   *right;

    left = ft_parse_redirection(token);
    while (*token && (*token)->type == TK_PIPE)
    {
        *token = (*token)->next;
        right = ft_parse_redirection(token);

    }
}

// < file1 echo hello (>> file.txt)

t_ast   *ft_parse_redirection(t_token **token)
{
    t_ast   *avant;
    t_ast   *apres;
    t_ast   *command;

    avant = 
}