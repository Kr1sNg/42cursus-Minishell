/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ast_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/25 21:00:33 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* support function of ft_parse_command */
void	ft_redirect_list_add(t_ast_redirect **head, t_ast_redirect *new)
{
	t_ast_redirect	*tmp;
	
	if (!head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/* support function of ft_parse_words, to check if these is '=' in WORDS */
bool	ft_words_assign(char *words)
{
	int	i;
	int	j;
	
	i = 0;
	while (words[i] && words[i] != '=')
	{
		printf("%c\n", words[i]);
		i++;
	}
	printf("index i: %i\n", i);
	printf("%c\n", words[5]);
	printf("%c\n", words[i + 1]);
	if (i == 0 || words[i + 1] == '\0')
		return (false);
	j = 0;
	while (j < i)
	{
		if (!ft_isalnum(words[j]) && words[j] != '_' && words[j] != '$') // example USER=TAT_HOANG
			return (false);
		j++;
	}
	printf("index j: %i\n", j);
	return (true);
}

int	main(void)
{
	printf("%i\n", ft_words_assign("$USER=kris"));
}