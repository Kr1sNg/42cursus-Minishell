/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:02:29 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/21 16:02:27 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildins.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*var_export_only(char *line)
{
	char	*dest;
	int		i;
	int		check;

	i = 0;
	check = 0;
	dest = malloc((ft_strlen(line) + 3) * sizeof(char));
	while(line[i - check])
	{
		if (check == 0 && i > 0 && line[i - 1] == '=')
		{
			dest[i] = '\"';
			check = 1;
		}
		else
			dest[i] = line[i - check];
		i++;
	}
	dest[i] = '\"';
	dest[i + 1] = '\0';
	return (dest);
}

char	*convert_line_export(char *line)
{
	char	*dest;
	char	*src_mdf;
	int		i;
	
	i = 0;
	dest = malloc((ft_strlen(line) + 14) * sizeof(char));
	src_mdf = var_export_only(line);
	dest = ft_strjoin("declare -x ", src_mdf);
	dest[ft_strlen(src_mdf) + 11] = '\0';
	return (dest);
}

void	ft_swap(char **str, char **str2)
{
	char *tmp;

	tmp = *str;
	*str = *str2;
	*str2 = tmp;
}

char	**ft_sort_a(char **env)
{
	int	check;
	int	i;
	int	j;

	i = 0;
	j = 0;
	check = 1;
	while(env[i])
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

int		ft_strlen_name_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	cmd_env(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
}

char	**cmd_env_unset(char **env, char *cmd)
{
	char	**env_cpy;
	t_init	index;

	index.l = 0;
	index.i = 0;
	index.j = 0;
	index.k = 0;
	while (env[index.i])
		(index.i)++;
	env_cpy = (char **)malloc((index.i) * sizeof(int *));
	while (index.j + index.l < index.i - 1)
	{
		if (ft_strncmp(cmd, env[index.j + index.l], ft_strlen_name_env(env[index.j + index.l])) == 0)
			(index.l) += 1;
		env_cpy[index.j] = (char *)malloc(ft_strlen(env[index.j + index.l]));
		index.k = 0;
		while(env[index.j + index.l][index.k])
		{
			env_cpy[index.j][index.k] = env[index.j + index.l][index.k];
			(index.k)++;
		}
		env_cpy[index.j][index.k] = '\0';
		(index.j)++;
	}
	env_cpy[index.i - 1] = NULL;
	return (env_cpy);
}

char	**cmd_env_export(char **env, char *cmd)
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
	env_cpy = (char **)malloc((i + 2) * sizeof(int *));
	while (j < i)
	{
		env_cpy[j] = (char *)malloc(ft_strlen(env[j]));
		k = 0;
		while(env[j][k])
		{
			env_cpy[j][k] = env[j][k];
			k++;
		}
		env_cpy[j][k] = '\0';
		j++;
	}
	env_cpy[i] = ft_strcpy_test(env_cpy[i], cmd, ft_strlen(cmd));
	env_cpy[i + 1] = NULL;
	return (env_cpy);
}

char	**cmd_create_env(char **env)
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
		env_cpy[j] = (char *)malloc(ft_strlen(env[j]));
		k = 0;
		while(env[j][k])
		{
			env_cpy[j][k] = env[j][k];
			k++;
		}
		env_cpy[j][k] = '\0';
		j++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

char	**cmd_unset(char **env, char *cmd)
{
	char	**env_cpy;
	
	env_cpy = NULL;
	env_cpy =  cmd_env_unset(env, cmd);
	free_tab(env);
	return (env_cpy);
}

char	**cmd_export(char **env, char *cmd)
{
	char	**env_cpy;
	
	env_cpy = NULL;
	if (!cmd)
	{
		env_cpy = ft_print_sort_env(env);
		cmd_env(env_cpy);
		free_tab(env_cpy);
		return (NULL);
	}
	else
	{
		env_cpy =  cmd_env_export(env, cmd);
		free_tab(env);
		return (env_cpy);
	}
}

void	cmd_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
		printf("%s", pwd);
}

void	cmd_cd(char *str)
{
	chdir(str);
}
