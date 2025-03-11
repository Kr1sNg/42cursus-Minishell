/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 19:03:27 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	ft_free_command(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->command->cmd_words)
		ft_free_ast(ast->command->cmd_words);
	if (ast->command->redirect_list)
		ft_free_ast(ast->command->redirect_list);
	free(ast->command);
	free(ast);
}

void	ft_free_words(t_ast *words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words->cmd_words->args && words->cmd_words->args[i])
	{
		free(words->cmd_words->args[i]);
		i++;
	}
	free(words->cmd_words->args);
	free(words->cmd_words);
	free(words);
}

void	ft_free_redir_list(t_ast *redir_list)
{
	t_ast	*curr;
	t_ast	*next;
	t_ast	*tmp;

	curr = redir_list;
	while (curr)
	{
		next = NULL;
		if (curr->redirect)
		{
			free(curr->redirect->target);
			if (curr->redirect->next)
				next = curr->redirect->next;
			free(curr->redirect);
		}
		tmp = curr;
		curr = next;
		free(tmp);
	}
}
