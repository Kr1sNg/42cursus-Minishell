/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_split_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:29:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 22:30:17 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* these functions are to split command line into tokens */

static int	skip_spaces(const char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

static char	*handle_quote(const char *str, int *i)
{
	char	c;
	char	*token;

	c = str[(*i)++];
	token = ft_strdup_s((char *)(str + *i - 1));
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == c)
		(*i)++;
	return (token);
}

static char	*handle_operator(const char *str, int *i)
{
	char	*token;
	int		op_val;

	op_val = is_operator((char *)&str[*i]);
	token = ft_strdup_s((char *)(str + *i));
	if (op_val > 1)
		*i += 2;
	else
		(*i)++;
	return (token);
}

static char	*handle_word(const char *str, int *i)
{
	char	*token;

	token = ft_strdup_s((char *)(str + *i));
	while (str[*i] && !ft_isspace(str[*i])
		&& !is_quote(str[*i]) && !is_operator((char *)&str[*i]))
		(*i)++;
	return (token);
}

char	**ft_split_tokens(char *str)
{
	int		i;
	int		j;
	char	**arrs;
	char	*token;

	i = 0;
	arrs = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!arrs)
		return (NULL);
	j = 0;
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		if (is_quote(str[i]))
			token = handle_quote(str, &i);
		else if (is_operator(&str[i]))
			token = handle_operator(str, &i);
		else
			token = handle_word(str, &i);
		arrs[j++] = token;
	}
	return (arrs);
}
