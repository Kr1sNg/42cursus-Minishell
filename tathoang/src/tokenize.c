/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/20 21:12:58 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// builtin: echo, cd, pwd, export, unset, env, exit
// quote: " ", ' '
// open: $
// operation: |, ||, &&
// redirect: >, <, >>, <<
// option: -n


// echo "    hello   "


/* split cmd, word, operations */


/* create a new token node and add its type */
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
	char 	**words;

	tokens = NULL;
	i = 0;
	words = ft_split_tokens(input);
	if (!words)
		return (NULL);
	while (words[i])
	{
		ft_token_add_back(&tokens, words[i]);
		i++;
	}
	return (tokens);
}

