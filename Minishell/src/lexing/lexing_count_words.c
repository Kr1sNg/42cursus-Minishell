/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_count_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:29:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 22:29:46 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* these functions are to count all tokens in command line */

static int	skip_spaces(char *s, int i)
{
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}

static int	handle_quote(char *s, int *i)
{
	char	c;

	c = s[(*i)++];
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i] != c)
		return (-42);
	(*i)++;
	return (1);
}

static int	handle_operator(char *str, int *i)
{
	if (is_operator(&str[*i]) > 1)
		(*i)++;
	(*i)++;
	return (1);
}

static int	handle_word(char *str, int *i)
{
	int		count;

	count = 1;
	while (str[*i] != '\0' && !ft_isspace(str[*i])
		&& !is_quote(str[*i]) && !is_operator(&str[*i]))
		(*i)++;
	return (count);
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		i = skip_spaces(str, i);
		if (str[i] != '\0' && is_quote(str[i]))
			count += handle_quote(str, &i);
		else if (str[i] != '\0' && is_operator(&str[i]))
			count += handle_operator(str, &i);
		else if (str[i] != '\0')
			count += handle_word(str, &i);
	}
	return (count);
}
