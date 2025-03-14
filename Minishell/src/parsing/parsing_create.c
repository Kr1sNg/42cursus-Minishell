/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 15:16:41 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* create new node */
void	ft_new_ast_node(t_ast **node, t_ast_type type)
{
	*node = ft_calloc(1, sizeof(t_ast));
	if (!(*node))
		return ;
	(*node)->type = type;
}

t_ast	*ft_create_ast_redirect(t_token_type direction, char *target)
{
	t_ast	*node;

	if (!target)
		return (ft_error_syntax("newlinetarget", NULL), NULL);
	ft_new_ast_node(&node, AST_REDIRECT);
	if (node)
	{
		node->redirect = ft_calloc(1, sizeof(*node->redirect));
		if (!node->redirect)
			return (free(node), NULL);
		node->redirect->direction = direction;
		node->redirect->target = target;
		node->redirect->next = NULL;
	}
	return (node);
}

t_ast	*ft_create_ast_words(char **args)
{
	t_ast	*node;

	ft_new_ast_node(&node, AST_WORDS);
	if (node)
	{
		node->cmd_words = ft_calloc(1, sizeof(*node->cmd_words));
		if (!node->cmd_words)
			return (free(node), NULL);
	}
	node->cmd_words->args = args;
	return (node);
}
