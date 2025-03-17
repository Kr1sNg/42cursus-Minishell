/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:57:03 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/17 19:54:01 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

// int ft_search(char *base, char *in)
// {
// 	int	i;
// 	int	j;
// 	int	k;
// 	int	result;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	result = 0;
// 	while (base[i] == '*')
// 		i++;
// 	while (in[j] != '\0')
// 	{
// 		while (in[j + k] == base[i + k] && in[j + k] != '\0')
// 			i++;
// 		if (base[i] == '\0')
// 			return (1);
// 		else if (base[i + k] == '*')
// 			return(ft_search(&base[i + k], &in[j]));
// 		j++;
// 		i = 0;
// 	}
// 	return (0);
// }

// int	ft_check_valid_wc(char *base, char *in)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (base[i] && in[j] && base[i] - in[j] != 0)
// 	{
// 		if (base[i] == '*')
// 			return (ft_search());
// 		else if (ft_strcmp(base, in) == '*')
// 			return (ft_search());
// 		else
// 			return (0);
// 	}
// 	return (1);
// }

int	ft_check_valid_wc(char *base, char *in)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (base[i] && in[j] && base[i] - in[j] != 0)
	{
		while (base[i] && in[j] && base[i++] == '*')
			check = 1;
		if (check == 1)
		{
			if (!base[i])
				break ;
			while (base[i] && in[j] && base[i] != in[j])
				j++;
		}
		else if ((!base[i] || !in[j]) || base[i] != in[j])
			return (0);
		else if (!base[i] && !in[j])
			break ;
		while (base[i] && in[j] && base[i] == in[j++])
			j++;
		if ((!base[i] || !in[j]) && (base[i] || in[j]))
			return (0);
	}
	return (1);
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
