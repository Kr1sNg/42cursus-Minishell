/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/05 13:07:09 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* PARSING GRAMMAR
// [...] means Zero or once
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

/* start to convert tokens list into an abstract syntax tree */

// <COMMAND_LINE>    	::= <LOGICAL>
t_ast	*ft_parse(t_token *token)
{
    t_ast   *ast;
    
    // printf("ft_pars\n\n");
    ast = ft_parse_logical(&token);
    if (token) //extra token after command line
    {
        if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT
            || token->type == TK_APPEND_OUT || token->type == TK_HEREDOC)
            ft_error_syntax("newline");
        else
            ft_error_syntax(token->word);
        ft_free_ast(ast);
        return (NULL);
    }
    return (ast);
}

//<LOGICAL>       	::= <PIPELINE> { ("&&" | "||") <PIPELINE> }
t_ast   *ft_parse_logical(t_token **token)
{
    t_token_type    operator;
    t_ast           *left;
    t_ast           *right;
    char            c;

    left = ft_parse_pipeexpr(token);
    while ((*token) && ((*token)->type == TK_AND || (*token)->type == TK_OR))
    {
        c = (*token)->word[0];
        operator = (*token)->type;
        *token = (*token)->next;
        right = ft_parse_pipeexpr(token);
        if (!right)
        {
            ft_free_ast(left);
            if (c == '|')
                return (ft_error_syntax("||"), NULL);
            else
                return (ft_error_syntax("&&"), NULL);
        }
        left = ft_create_ast_logical(operator, left, right);
    }
    return (left);
}

//<PIPEEXPR>       	::= <EXPRESSION> { "|" <EXPRESSION> }
t_ast   *ft_parse_pipeexpr(t_token **token)
{
    t_ast   *left;
    t_ast   *right;

    left = ft_parse_expression(token);
    right = NULL;
    while (*token && (*token)->type == TK_PIPE)
    {
        *token = (*token)->next;
        if (!(*token))
        {
            ft_free_ast(left);
            return (ft_error_syntax("|"), NULL); //need free before
        }
        right = ft_parse_expression(token);
        left = ft_create_ast_pipeexpr(left, right);
    }
    return (left);
}

//<EXPRESSION>     	::= <COMMAND>  -> type NO_PARENTHESE
//                  | <SUBSHELL -> type PARENTHESE => "(" <LOGICAL> ")" [ <REDIR_LIST> ]
t_ast   *ft_parse_expression(t_token **token)
{   
    t_ast       *expression;
    
    if (*token && (*token)->type == TK_SUBSHELL_OPEN)
    {
        expression = ft_parse_subshell(token);
        return (ft_create_ast_expression(expression, true));
    }
    else
    {
        expression = ft_parse_command(token);
        return (ft_create_ast_expression(expression, false));
    }
    return (ft_error_syntax("("), NULL);
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
    {
        ft_free_ast(ahead);  // need to check how to run only ">> file1" ?
        return (NULL); // if there's no command words, it means we've returned "command not found: args[0]"
    }
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
        {
            ft_free_ast(logical);
            return (ft_error_syntax("("), NULL);
        }
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
    while (current && (current->type == TK_WORD || current->type == TK_DQUOTE || current->type == TK_SQUOTE))
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
//<REDIRECTION>     	::= (">" | "<" | ">>") <WORD>
//						| "<<" <WORD>
// ex: echo hello "< file1 >> file2 > file3"
t_ast   *ft_parse_redirect(t_token **token) //t_ast list of redirect
{
    t_ast           *head;
    t_ast           *curr;
    t_token_type    direction;
    char            *target;

    head = NULL;
    while (*token && (*token)->next && ((*token)->type == TK_REDIR_IN || (*token)->type == TK_REDIR_OUT
            || (*token)->type == TK_APPEND_OUT || (*token)->type == TK_HEREDOC))
    {
        direction = (*token)->type;
        *token = (*token)->next;
        if (!(*token) || (*token)->type != TK_WORD)
        {
            ft_free_ast(head);
            return (ft_error_syntax("newline"), NULL);
        }
        target = ft_strdup((*token)->word);
        if (!target)
            return (NULL);
        curr = ft_create_ast_redirect(direction, target);
        if (!curr)
        {
            free(target);
            ft_free_ast(head);
            return (ft_error_syntax("newline"), NULL);
        }
        if (!head)
            head = curr;
        else
            ft_redir_list_add(&head, curr);
        *token = (*token)->next;
    }
    return (head);
}




