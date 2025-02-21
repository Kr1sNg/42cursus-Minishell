/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/21 17:10:34 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// echo -> hi ->  || -> pwd
// token->token->token->token->NULL
//=> read token, -> take  until see the node?
// => execute node ???



/* one token look-ahead */
void	ft_next_token(t_token **current)
{
	if (current && *current)
		*current = (*current)->next;
}

t_tree	ft_parse_cmd(t_token *head)
{
	t_tree	*cmd;
	t_token	*end;
	
	end = head;
	while (end)
		end = head->next;
	cmd = ft_parse_line(&head, end);
	
	
}


int ft_parse_exec(t_token *token)
{
	
}

int	ft_parse_redir(t_token *token);

t_tree ft_parse_pipe(t_token **start, t_token *end) // return pointer to tree
{
	t_tree	*new_node;
	
	new_node = ft_parse_exec(start, end);
	if ()
	
}

int ft_parse_line(t_token *token);

int ft_parse_block(t_token *token)


/*
- differnt kinds of node: EXEC (non-terminal symbol), BLOCK, 

- parseblock read in '(' recursive call parseline, scan ')' and call parsedirs

*/
