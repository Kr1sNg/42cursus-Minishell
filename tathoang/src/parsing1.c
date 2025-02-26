/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/26 18:14:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* start to convert tokens list into an abstract syntax tree */

// <COMMAND_LINE>    	::= <LOGICAL>
t_ast	*ft_parse(t_token **token)
{
    t_ast   *ast;
    
    ast = ft_parse_logical(token);
    if (*token) //extra token after command line
    {
        ft_free_logical(ast); //TODO
        return (ft_error_input(200), NULL);
    }
    return (ast);
}

//<LOGICAL>       	::= <PIPELINE> { ("&&" | "||") <PIPELINE> }
t_ast   *ft_parse_logical(t_token **token)
{
    t_token_type    logical;
    t_ast           *left;
    t_ast           *right;

    left = ft_parse_pipeline(token);
    while ((*token) && ((*token)->type == TK_AND || (*token)->type == TK_OR))
    {
        logical = (*token)->type;
        *token = (*token)->next;
        right = ft_parse_pipeline(token);
        if (!right)
        {
            ft_free_logical(left);
            return (ft_error_syntax("&& or ||"), NULL);
        }
        left = ft_create_ast_logical(logical, left, right);
    }
    return (left);
}

//<PIPELINE>       	::= <EXPRESSION> { "|" <EXPRESSION> }
t_ast   *ft_parse_pipeline(t_token **token)
{
    t_ast   *left;
    t_ast   *right;

    left = ft_parse_expression(token);
    right = NULL;
    while (*token && (*token)->type == TK_PIPE)
    {
        *token = (*token)->next;
        right = ft_parse_expression(token);
        left = ft_create_ast_pipeline(left, right);
    }
    return (left);
}

//<EXPRESSION>     	::= <COMMAND>  -> type NO_PARENTHESE
//                  | <SUBSHELL -> type PARENTHESE => "(" <LOGICAL> ")" [ <REDIR_LIST> ]
t_ast   *ft_parse_expression(t_token **token)
{   
    if (*token && (*token)->type == TK_SUBSHELL_OPEN)
        return (ft_parse_subshell(token));
    return (ft_parse_command(token));
}

//<COMMAND>         	::= [ <REDIR_LIST> ] <CMD_WORDS> [ <REDIR_LIST> ]
t_ast   *ft_parse_command(t_token **token)
{
    t_ast  *ahead;
    t_ast  *cmd_words;
    t_ast  *behind;

    ahead = ft_parse_redirect(token);
    cmd_words = ft_parse_words(token);
    if (!cmd_words)
        return (ft_error_input(-200), NULL);
    behind = ft_parse_redirect(token);
    return (ft_create_ast_command(ahead, cmd_words, behind));
}

//<SUBSHELL>          ::= "(" <LOGICAL> ")" [ <REDIR_LIST> ]
t_ast   *ft_parse_subshell(t_token **token)
{
    t_ast   *logical;
    t_ast   *redir_list;

    redir_list = NULL;
    if (*token && (*token)->type == TK_SUBSHELL_OPEN)
    {
        *token = (*token)->next;
        logical = ft_parse_logical(token);
        if (!logical || !*token || (*token)->type != TK_SUBSHELL_CLOSE)
            return (ft_error_syntax("("), NULL);
        *token = (*token)->next;
        if (*token)
            redir_list = ft_parse_redirect(token);
        return (ft_create_ast_subshell(logical, redir_list));
    }
    return (ft_error_syntax("("), NULL);
}

//<CMD_WORDS>       	::= <WORD> { <WORD> }
t_ast   *ft_parse_words(t_token **token)
{
    t_token *current;
    int     argc;
    char    **args;
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
    args = ft_calloc((argc + 1), sizeof(char *));
    i = 0;
    while (i < argc)
    {
        args[i++] = ft_strdup((*token)->word);
        *token = (*token)->next;
    }
    args[argc] = NULL;
    return (ft_create_ast_words(args));
}

//<REDIR_LIST>      	::= <REDIRECTION> { <REDIRECTION> }

t_ast   *ft_parse_redirect(t_token **token) //t_ast list of redirect
{
    t_ast           *head;
    t_ast           *curr;
    t_token_type    direction;
    char            *target;

    head = NULL;
    while (*token && ((*token)->type == TK_REDIR_IN || (*token)->type == TK_REDIR_OUT
            || (*token)->type == TK_APPEND_OUT || (*token)->type == TK_HEREDOC))
    {
        direction = (*token)->type;
        *token = (*token)->next;
        if (!(*token) || (*token)->type != TK_WORD)
        {
            ft_free_ast_lst(head);
            return (ft_error_input(-300), NULL);
        }
        target = ft_strdup((*token)->word);
        curr = ft_create_ast_redirect(direction, target);
        if (!curr)
        {
            ft_free_ast_lst(head);
            return (ft_error_input(-300), NULL);
        }
        if (!head)
            head = curr;
        else
            ft_redir_list_add(&head, curr);
        (*token) = (*token)->next;
    }
    return (head);
}




