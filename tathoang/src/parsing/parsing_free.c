/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/27 20:52:22 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_free_ast(t_ast *ast)
{
    if (!ast)
        return ;
    ft_free_logical(ast);
    // if (ast->type == AST_LOGICAL)
	// 	ft_free_logical(ast);
	// else if (ast->type == AST_PIPEEXPR)
	//  	ft_free_pipeexpr(ast);
	// else if	(ast->type == AST_EXPRESSION)
	// 	ft_free_expression(ast);
	// else if (ast->type == AST_SUBSHELL)
	// 	ft_free_subshell(ast);
	// else if (ast->type == AST_COMMAND)
	// 	ft_free_command(ast);
	// else if (ast->type == AST_WORDS)
	// 	ft_free_words(ast);
	// else if (ast->type == AST_REDIRECT)
	// 	ft_free_redir_list(ast);
}

void    ft_free_logical(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->u_ast_data.logical.left)
        ft_free_pipeexpr(ast->u_ast_data.logical.left);
    if (ast->u_ast_data.logical.right)
        ft_free_pipeexpr(ast->u_ast_data.logical.right);
    //free(ast);
}

void    ft_free_pipeexpr(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->u_ast_data.pipeexpr.left)
        ft_free_expression(ast->u_ast_data.pipeexpr.left);
    if (ast->u_ast_data.pipeexpr.right)
        ft_free_expression(ast->u_ast_data.pipeexpr.right);
    //free(ast);
}

void    ft_free_expression(t_ast *ast)
{
    if (!ast)
        return ;
    printf("\tfree_expression\n\n");
    printf("\ttype in expression: %i\n\n", ast->type);
    if (ast->u_ast_data.expression.command)
        ft_free_command(ast->u_ast_data.expression.command);
    else //3
    {   
        // printf("type here: %i\n", ast->type);
        ft_free_ast(ast->u_ast_data.expression.subshell);
    }
    //free(ast);
}

void    ft_free_subshell(t_ast *ast)
{
    if (!ast)
        return ;
    write(1, "bon\n\n", 5);
    if (ast->u_ast_data.subshell.logical)
        ft_free_logical(ast->u_ast_data.subshell.logical);
    if (ast->u_ast_data.subshell.redirect_list)
        ft_free_redir_list(ast->u_ast_data.subshell.redirect_list);
    //free(ast);
}

void    ft_free_command(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->u_ast_data.command.cmd_words)
        ft_free_words(ast->u_ast_data.command.cmd_words);
    if (ast->u_ast_data.command.redirect_list)
        ft_free_redir_list(ast->u_ast_data.command.redirect_list);
    write(1, "bon\n\n", 5);
    //free(ast);
}

void    ft_free_words(t_ast *words)
{
    int i;
    
    if (!words)
        return ;
    i = 0;
    while (words->u_ast_data.cmd_words.args && words->u_ast_data.cmd_words.args[i])
    {
        write(1, "oui\n\n", 5);
        
        free(words->u_ast_data.cmd_words.args[i]);
        i++;
    }
    free(words->u_ast_data.cmd_words.args);
    // free(words);
}

void	ft_free_redir_list(t_ast *redir_list)
{
	t_ast	*tmp;

	if (!redir_list)
		return ;
	while (redir_list)
	{
		tmp = redir_list;
		if (!tmp->u_ast_data.redirect.target)
			free(tmp->u_ast_data.redirect.target);
		redir_list = redir_list->u_ast_data.redirect.next;
		free(tmp);
	}
    //free(redir_list);
}

