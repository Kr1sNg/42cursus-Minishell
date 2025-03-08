/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:02:29 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/08 18:25:12 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/buildins.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_strlen_name_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	ft_display_export(char **env)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (env[i])
	{
		j = 0;
		check = 0;
		while(env[i][j])
		{
			if (env[i][j] == '\"' && env[i][j + 1])
			{
				if (check++ > 0)
					printf("\\");
			}
			printf("%c", env[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	cmd_create_env(t_env *infos, char **env)
{
	char	**env_cpy;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (env[i])
		i++;
	env_cpy = (char **)malloc((i + 1) * sizeof(int *));
	while (j < i)
	{
		env_cpy[j] = (char *)malloc((ft_strlen(env[j]) + 1) * sizeof(char));
		k = 0;
		while (env[j][k])
		{
			env_cpy[j][k] = env[j][k];
			k++;
		}
		env_cpy[j][k] = '\0';
		j++;
	}
	env_cpy[i] = NULL;
	infos->env = env_cpy;
}
