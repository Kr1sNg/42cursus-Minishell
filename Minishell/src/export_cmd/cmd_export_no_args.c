/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_no_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:46:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/10 09:29:35 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"



void	ft_swap(char **str, char **str2)
{
	char	*tmp;

	tmp = *str;
	*str = *str2;
	*str2 = tmp;
}

char	**ft_sort_a(char **env)
{
	// int	check;
	int	i;
	int	j;

	i = 0;
	j = 0;
	// check = 1;
	while (env[i])
	{
		j = i;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				ft_swap(&env[i], &env[j]);
			j++;
		}
		i++;
	}
	return (env);
}

char	*convert_line_export(char *line)
{
	char	*dest;
	char	*src_mdf;
	// int		i;

	// i = 0;
	src_mdf = var_export_only(line);
	dest = ft_strjoin("declare -x ", src_mdf);
	dest[ft_strlen(src_mdf) + 11] = '\0';
	free(src_mdf);
	return (dest);
}

char	**ft_print_sort_env(char **env)
{
	char	**env_cpy;
	t_init	index;

	index.i = 0;
	index.j = 0;
	while (env[index.i])
		(index.i)++;
	env_cpy = (char **)malloc((index.i + 1) * sizeof(int *));
	while (index.j < index.i)
	{
		env_cpy[index.j] = convert_line_export(env[index.j]);
		(index.j)++;
	}
	env_cpy[index.i] = NULL;
	env_cpy = ft_sort_a(env_cpy);
	return (env_cpy);
}
