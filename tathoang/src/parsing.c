/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/19 16:35:00 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


/* one token look-ahead */
void	ft_next_token(t_token **current)
{
	if (current && *current)
		*current = (*current)->next;
}




int ft_parsing(t_token *token)
{
	
}


/*
- differnt kinds of node: EXEC (non-terminal symbol), BLOCK, 

- parseblock read in '(' recursive call parseline, scan ')' and call parsedirs

*/
