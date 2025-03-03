/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/03 18:15:39 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	printf("token:");
	while (head)
	{
		printf("- [%s] ", head->word);
		head = head->next;
	}
	printf("\n");
}

/* put cmd/arg into list */
t_token	*ft_tokenize(char *input)
{
	t_token	*tokens;
	char 	**words;
	int		i;

	tokens = NULL;
	words = ft_split_tokens(input);
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
		ft_token_add_back(&tokens, words[i++]);
	ft_split_free(words);
	return (tokens);
}

