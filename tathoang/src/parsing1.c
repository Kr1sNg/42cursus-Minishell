/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/25 21:22:00 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* start to convert tokens list into an abstract syntax tree */

// <COMMAND_LINE>    	::= <LOGICAL>
t_ast	*ft_parse(t_token *token)
{
    t_ast   *ast;
    
    ast = ft_parse_logical(&token);
    if (token) //extra token after command line
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

    left = ft_parse_pipeline(token); //TODO
    logical = TK_EOF;
    right = NULL;
    while ((*token) && ((*token)->type == TK_AND || (*token)->type == TK_OR))
    {
        logical = (*token)->type;
        *token = (*token)->next;
        right = ft_parse_pipeline(token);
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
//                  | "(" <LOGICAL> ")" -> type PARENTHESE
t_ast   *ft_parse_expression(t_token **token)
{   
    t_ast   *expr;
    
    if (*token && (*token)->type == TK_SUBSHELL_OPEN)
    {
        *token = (*token)->next;
        expr = ft_parse_logical(token);
        if (*token && (*token)->type == TK_SUBSHELL_CLOSE)
        {
            *token = (*token)->next;
            if (*token && (*token)->type == TK_WORD)
                return (ft_error_input(-200), NULL); // need to check and clear
            return (ft_create_ast_expression(expr));
        }
        else if (*token == NULL)
            return (ft_error_input(-200), NULL); // need to check and clear
    }
    return (ft_parse_command(token));
}

//<COMMAND>         	::= [ <REDIR_LIST> ] <CMD_WORDS> [ <REDIR_LIST> ]
t_ast   *ft_parse_command(t_token **token)
{
    t_ast_command   *cmd;
    t_ast_redirect  *redir;

    cmd = ft_calloc(1, sizeof(t_ast_command));
    if (!cmd)
        return (NULL);
    while (*token && ((*token)->type == TK_REDIR_IN || (*token)->type == TK_REDIR_OUT
            || (*token)->type == TK_APPEND_OUT || (*token)->type == TK_HEREDOC))
    {
        redir = ft_parse_redirect(token); //TODO must have token = token->next
        ft_redirect_list_add(&(cmd->redirect_list), redir);
    }
    cmd->cmd_words = ft_parse_words(token);
    if (!cmd->cmd_words)
        return (ft_error_input(-210), NULL);
    while (*token && ((*token)->type == TK_REDIR_IN || (*token)->type == TK_REDIR_OUT
            || (*token)->type == TK_APPEND_OUT || (*token)->type == TK_HEREDOC))
    {
        redir = ft_parse_redirect(token); //TODO
        ft_redirect_list_add(&(cmd->redirect_list), redir);
    }
    return (cmd); //t_ast_command not t_ast !!
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
        args[i++] = (*token)->word;
        *token = (*token)->next;
    }
    args[argc] = NULL;
    return (ft_create_ast_words(args));
}

t_ast   *ft_parse_redirect(t_token **token)
{
    t_ast   *redir;

    redir = NULL;
    while (*token && ((*token)->type == TK_REDIR_IN || (*token)->type == TK_REDIR_OUT
            || (*token)->type == TK_APPEND_OUT || (*token)->type == TK_HEREDOC))
    {
        redir->type = AST_REDIRECT;
        redir->u_ast_data.redirect.direction = (*token)->type;
        redir->u_ast_data.redirect.target = (*token)->next->word;
        if 
    }        
} ????????????????????????????????????????


