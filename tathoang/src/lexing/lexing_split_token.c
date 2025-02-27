/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_split_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:29:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/27 15:51:44 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* these functions are to split command line into tokens */

static int	is_operator(char *s)
{	
	if ((s[0] == '|' || s[0] == '>' || s[0] == '<') && s[1])
	{
		if (s[1] == s[0])
			return (11);
		else if (s[1] && (ft_isalnum(s[1]) || ft_isspace(s[1])))
			return (1);
		else
			return (ft_error_input(-42), -42);
	}
	else if (s[0] == '(' || s[0] == ')')
		return (1);
	else if (s[0] == '&' && s[1])
	{
		if (s[1] == s[0])
			return (22);
		else
			return (ft_error_input(-42), -42);
	}
	return (0);
}
static int is_quote(char c)
{
	if (c == '\"')
		return (34);
	else if (c == '\'')
		return (39);
	else
		return (0);
}	

static int	count_words(char *str)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while ((str[i] != '\0') && ft_isspace(str[i]))
			i++;
		if ((str[i] != '\0') && is_quote(str[i]))
		{
			c = str[i++];
			count++;
			while (str[i] != '\0' && str[i] != c)
				i++;
			if (str[i] != c)
				return (ft_error_input(-42), -42);
			i++;
		}
		else if ((str[i] != '\0') && is_operator(&str[i]))
		{
			if (is_operator(&str[i]) > 1)
				i++;
			i++;
			count++;
		}
		else if (str[i] != '\0' && !ft_isspace(str[i]) && !is_quote(str[i] && !is_operator(&str[i])))
		{
			count++;
			while (str[i] != '\0' && !ft_isspace(str[i]) && !is_quote(str[i]) && !is_operator(&str[i]))
				i++;
		}
	}
	return (count);
}

static int	count_letter_quote(char *s, char c)
{
	int	i;

	i = 0;
	c = s[i++];
	while (s[i] && s[i] != c)
		i++;
	i++;
	return (i);
}

static int	count_letter(char *str)
{
	int	i;
	
	i = 0;
	if (str[i] && is_operator(&str[i]) == 1)
		return (1);
	else if (str[i] && is_operator(&str[i]) > 1)
		return (2);
	else if (str[i] && is_quote(str[i]))
		return(count_letter_quote(&str[i], str[i]));
	else
	{
		while ((str[i] != '\0') && !ft_isspace(str[i]) && !is_quote(str[i]) && !is_operator(&str[i]))
			i++;
	}
	return (i);
}

static char	*ft_strdup_s(char *src)
{
	int		i;
	int		len;
	char	*arr;

	i = 0;
	// if (is_quote(src[0]))
	// 	return (ft_dup_quote(src));
	len = count_letter(src);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	**ft_split_tokens(char *str)
{
	int		i;
	int		j;
	char	**arrs;
	char	c;

	i = 0;
	j = 0;
	arrs = malloc(sizeof(char *) * (count_words(str) + 1));
	if (!arrs)
		return (NULL);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		if (str[i] && is_quote(str[i]))
		{
			arrs[j++] = ft_strdup_s(str + i);
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			i = i + 1;
		}
		else if (str[i] && is_operator(&str[i]))
		{
			arrs[j++] = ft_strdup_s(str + i);
			if (is_operator(&str[i]) > 1)
				i++;
			i++;
		}
		else if (str[i] != '\0' && !ft_isspace(str[i]) && !is_quote(str[i] && !is_operator(&str[i])))
		{
			arrs[j++] = ft_strdup_s(str + i);
			while (str[i] != '\0' && !ft_isspace(str[i]) && !is_quote(str[i]) && !is_operator(&str[i]))
				i++;
		}
	}
	arrs[j] = NULL;
	return (arrs);
}


/*
#include <stdio.h>
int	main(void)
{
	char **arrs;
	char *str = "echo \"   hello ||&&  \' \'   \" |  echo    hi&&pwd   $WORD";
	int i = 0;
	arrs = ft_split_tokens(str);
	if (!arrs)
		return (1);
	while (arrs[i] != NULL)
	{
		printf("%s\n", arrs[i]);
		free(arrs[i]);
		i++;
	}
	free(arrs);
	return (0);
}
*/
