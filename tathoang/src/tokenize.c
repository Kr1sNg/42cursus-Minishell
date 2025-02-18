/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/18 18:13:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// /* add type of token */
// t_type	ft_add_type(t_token *token, char *input)
// {
// 	if 
// }


/* create a new token node */
t_token	*ft_create_token(char *input)
{
	t_token	*new;
	
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(input);
	new->option = NULL;
	new->next = NULL;
	return (new);
}
/* add cmd/argument to the list */
void	ft_token_add_back(t_token **head, char *input)
{
	t_token	*new;
	t_token	*curr;

	new = ft_create_token(input);
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

/* free tokens */
void	ft_free_token(t_token *head)
{
	t_token	*tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		free(tmp);
	}
}

/* for debug and test */
void	ft_print_token(t_token *head)
{
	while (head)
	{
		printf("token: [%s]\n", head->cmd);
		head = head->next;
	}
}

/* put cmd/arg into list */
t_token	*ft_tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	char 	**cmd;

	tokens = NULL;
	i = 0;
	cmd = ft_split(input, ' ');
	if (!cmd)
		return (NULL);
	while (cmd[i])
	{
		ft_token_add_back(&tokens, cmd[i]);
		i++;
	}
	return (tokens);
}

