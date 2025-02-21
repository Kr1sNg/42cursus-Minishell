/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 00:02:29 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/21 02:00:15 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/buildins.h"

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
	printf("\n");
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
		(index.j)++;
	}
	env_cpy[index.i - 2] = NULL;
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
		j++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

char	**cmd_unset(char **env, char *cmd)
{
	char	**env_cpy;
	
	env_cpy = NULL;
	//if (!cmd)
	//	ft_print_sort_env
	//else
	//{
	env_cpy =  cmd_env_unset(env, cmd);
	free(env);
	//}
	return (env_cpy);
}

char	**cmd_export(char **env, char *cmd)
{
	char	**env_cpy;
	
	env_cpy = NULL;
	//if (!cmd)
	//	ft_print_sort_env
	//else
	//{
	env_cpy =  cmd_env_export(env, cmd);
	free(env);
	//}
	return (env_cpy);
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


