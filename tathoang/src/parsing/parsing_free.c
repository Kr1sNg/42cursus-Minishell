/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/28 21:09:12 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    ft_free_ast(t_ast *ast)
{
    if (!ast)
        return ;
    ft_free_logical(ast);
    printf("free ast\n");
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
    if (ast->logical->left)
    {
        ft_free_pipeexpr(ast->logical->left);
        printf("free ast logical left\n");
    }
    if (ast->logical->right)
    {
        ft_free_pipeexpr(ast->logical->right);
        printf("free ast logical right\n");
    }
    free(ast->logical);
    free(ast);
    printf("free ast logical\n");
}

void    ft_free_pipeexpr(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->pipeexpr->left)
    {
        printf("\tin piperxpr type left 1: %i\n", ast->pipeexpr->left->type);
        ft_free_expression(ast->pipeexpr->left);
        printf("free pipeexpr left\n");
    }
    if (ast->pipeexpr->right)
    {
        ft_free_expression(ast->pipeexpr->right);
        printf("free pipeexpr right\n");
    }
    free(ast->pipeexpr);
    free(ast);
    printf("free pipeexpr\n");
}

void    ft_free_expression(t_ast *ast)
{
    if (!ast)
        return ;
    printf("\tfree_expression\n\n");
    if (ast->type)
        printf("4* expression type: %i \n\n", ast->type);
    // printf("parantheses: %i\n\n", ast->expression->parenthesis);
    // printf("\ttype in expression 1: %i\n\n", ast->type);
    // if (ast->type == AST_LOGICAL)
	// 	ft_free_logical(ast);
	// if (ast->type == AST_PIPEEXPR)
	//  	ft_free_pipeexpr(ast);
	// if	(ast->type == AST_EXPRESSION)
	// 	ft_free_expression(ast);
	// if (ast->type == AST_SUBSHELL)
	// 	ft_free_subshell(ast);
	// if (ast->type == AST_COMMAND)
	// 	ft_free_command(ast->expression->subshell->command);
	// if (ast->type == AST_WORDS)
	// 	ft_free_words(ast);
	// if (ast->type == AST_REDIRECT)
	// 	ft_free_redir_list(ast);
    // printf("we stuck here!\n\n");
    if (ast->type == AST_COMMAND)
    {
        ft_free_command(ast->expression->command);
        printf("\ttype in expression 1: %i\n\n", ast->type);
    }
    else //3
    {   
        printf("*$*$ type here 2: %i\n", ast->type);
        free(ast);
    }
    
    // free(ast->expression);
    // free(ast);
}

void    ft_free_subshell(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->subshell->logical)
        ft_free_logical(ast->subshell->logical);
    if (ast->subshell->redirect_list)
        ft_free_redir_list(ast->subshell->redirect_list);
    free(ast->subshell);
    free(ast);
    printf("free subshell\n");
}

void    ft_free_command(t_ast *ast)
{
    if (!ast)
        return ;
    if (ast->command->cmd_words)
        ft_free_words(ast->command->cmd_words);
    if (ast->command->redirect_list)
        ft_free_redir_list(ast->command->redirect_list);
    free(ast->command);
    free(ast);
    printf("free command\n");
}

void    ft_free_words(t_ast *words)
{
    int i;
    
    if (!words)
        return ;
    i = 0;
    while (words->cmd_words->args && words->cmd_words->args[i])
    {
        write(1, "oui\n\n", 5);
        free(words->cmd_words->args[i]);
        i++;
    }
    free(words->cmd_words->args);
    free(words->cmd_words);
    free(words);
    printf("free words\n");
}

void	ft_free_redir_list(t_ast *redir_list)
{
	t_ast	*tmp;

	if (!redir_list)
		return ;
	while (redir_list)
	{
		tmp = redir_list;
		if (!tmp->redirect->target)
			free(tmp->redirect->target);
		redir_list = redir_list->redirect->next;
		free(tmp);
	}
    free(redir_list->redirect);
    free(redir_list);
    printf("free redir\n");
}

