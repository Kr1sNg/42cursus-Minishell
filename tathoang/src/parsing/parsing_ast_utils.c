/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ast_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/27 15:24:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* support function of ft_parse_command */

// to add new rediction into redirection_list
void	ft_redir_list_add(t_ast **head, t_ast *new)
{
	t_ast	*tmp;
	
	if (!new)
		return ;
	if (!(*head))
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->u_ast_data.redirect.next)
			tmp = tmp->u_ast_data.redirect.next;
		tmp->u_ast_data.redirect.next = new;
	}
}

// to free rediction list


