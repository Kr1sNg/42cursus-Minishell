/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/27 15:45:37 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_free_ast(t_ast *ast)
{
    if (!ast)
        return ;
    ft_free_logical(ast);
}

void    ft_free_logical(t_ast *ast)
{
    if (!ast)
        return ;
    ft_free_pipeexpr(ast->u_ast_data.logical.left);
    ft_free_pipeexpr(ast->u_ast_data.logical.right);
    free(ast);
}

void    ft_free_pipeexpr(t_ast *ast)
{
    if (!ast)
        return ;
    ft_free_expression(ast->u_ast_data.pipeexpr.left);
    ft_free_expresssion(ast->u_ast_data.pipeexpr.right);
    free(ast);
}

void    ft_free_expression(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->type == AST_SUBSHELL)
        ft_free_subshell(ast);
    else
        ft_free_command(ast);
}

void    ft_free_subshell(t_ast *ast)
{
    if (!ast)
        return ;
    ft_free_logical(ast->u_ast_data.subshell.logical);
    ft_free_redir_list(ast->u_ast_data.subshell.redirect_list);
    free(ast);
}

void    ft_free_command(t_ast *ast)
{
    if (!ast)
        return ;
    ft_free_words(ast->u_ast_data.command.cmd_words);
    ft_free_redir_list(ast->u_ast_data.command.redirect_list);
    free(ast);
}

void    ft_free_words(t_ast *words)
{
    int i;
    
    if (!words)
        return ;
    i = 0;
    while (words->u_ast_data.cmd_words.args[i])
    {
        free(words->u_ast_data.cmd_words.args[i]);
        i++;
    }
    free(words->u_ast_data.cmd_words.args);
    free(words);
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
    free(redir_list);
}

