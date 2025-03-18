/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:57:03 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/18 16:41:30 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int ft_search(char *base, char *in)
{
	int	i;
	int	s;
	int	result;

	i = 0;
	s = 0;
	result = 0;
	while (*base == '*')
		base++;
	if (base[0] == '\0')
		return (1);
	while (in[s] != '\0')
	{
		while (in[s + i] && base[i] && in[s + i] == base[i])
			i++;
		if (!base[i] && !in[s + i])
			return (1);
		else if (base[i] == '*' )
			result = ft_search(&base[i], &in[s + i]);
		s++;
		i = 0;
	}
	return (result);
}

int	ft_check_valid_wc(char *base, char *in)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (base[i] == '*')
		return (ft_search(base, in));
	while (base[i] == in[i])
		i++;
	if (base[i] == '*')
		return(ft_search(&base[i], &in[i]));
	else
		return (0);
}

int	ft_tablen_wc(char *cmd, char **wildcards)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (wildcards[i])
	{
		if (ft_check_valid_wc(cmd, wildcards[i]))
			j++;
		i++;
	}
	return (j);
}

int	ft_check_star(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}
