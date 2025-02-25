/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/25 14:30:17 by tat-nguy         ###   ########.fr       */
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


/* after spliting words, create nodes for each tokens and add its type */
t_token	*ft_create_token(char *word)
{
	t_token	*new;
	
	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = ft_strdup(word);
	new->type = ft_token_type(word);
	return (new);
}
/* add cmd/argument to the list */
void	ft_token_add_back(t_token **head, char *word)
{
	t_token	*new;
	t_token	*curr;

	new = ft_create_token(word);
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
		free(tmp->word);
		free(tmp);
	}
}

/* for debug and test */
void	ft_print_token(t_token *head)
{
	while (head)
	{
		printf("token: [%s]\n", head->word);
		head = head->next;
	}
}

/* put cmd/arg into list */
t_token	*ft_tokenize(char *input, int *token_count)
{
	t_token	*tokens;
	char 	**words;

	tokens = NULL;
	*token_count = 0;
	words = ft_split_tokens(input);
	if (!words)
		return (NULL);
	while (words[*token_count])
	{
		ft_token_add_back(&tokens, words[*token_count]);
		(*token_count)++;
	}
	return (tokens);
}

