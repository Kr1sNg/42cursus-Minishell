/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:49:09 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/01 20:24:56 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/buildins.h"

char	*ft_strcat_pipex(char *dest, char *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_pipex(char const *s1, char const *s2, char *sep)
{
	size_t	lens1;
	size_t	lens2;
	char	*ptr;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	ptr = malloc((lens1 + lens2 + 2) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[0] = '\0';
	ft_strcat_pipex(ptr, (char *) s1);
	ft_strcat_pipex(ptr, sep);
	ft_strcat_pipex(ptr, (char *) s2);
	return (ptr);
}

char	*ft_getpath(char *name, char **path)
{
	int		i;
	char	*try_path;
	char	*cmd_name;

	i = 0;
	try_path = NULL;
	cmd_name = ft_findname(name);
	while (path[i])
	{
		try_path = (ft_strjoin_pipex(path[i], cmd_name, "/"));
		if (access(try_path, F_OK | X_OK) == 0)
		{
			free(cmd_name);
			return (try_path);
		}
		free(try_path);
		i++;
	}
	free(cmd_name);
	return (NULL);
}

char	*ft_getenv(char *name, char **env)
{
	char	*line_path;
	char	**possible_path;
	char	*path;
	int		i;

	i = 0;
	line_path = NULL;
	while (env[i])
	{
		line_path = ft_strnstr(env[i], "PATH=", 5);
		if (line_path)
		{
			while (line_path[0] != '=')
				line_path++;
			line_path++;
			possible_path = ft_split(line_path, ':');
			path = ft_getpath(name, possible_path);
			ft_free_tab(possible_path);
			return (path);
		}
		i++;
	}
	return (NULL);
}
