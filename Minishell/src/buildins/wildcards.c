/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:12:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/17 18:02:15 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	ft_fill_new_tab(char **new_cmd, char **cmd, char **wildcards, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (cmd[k])
	{
		if (k != j)
		{
			new_cmd[i] = ft_strdup(cmd[k]);
			i++;
		}
		k++;
	}
	k = 0;
	while (wildcards[k])
	{
		if (ft_check_valid_wc(cmd[j], wildcards[k]))
			new_cmd[i++] = ft_strdup(wildcards[k]);
		k++;
	}
	free_tab(wildcards);
	free_tab(cmd);
	new_cmd[i] = NULL;
}

char	*ft_strjoin_replace(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return ((char *)(s2));
	else if (!s2)
		return ((char *)(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!new)
		return (NULL);
	new[0] = '\0';
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	free(s1);
	free(s2);
	return (new);
}

char	**ft_malloc_new_tab(int fd, char **cmd, int j)
{
	char	**new_cmd;
	char	**wildcards;
	char	*buffer;
	char	*line;
	int		i;

	i = 0;
	buffer = NULL;
	line = get_next_line(fd);
	while (buffer || i++ == 0)
	{
		buffer = get_next_line(fd);
		line = ft_strjoin_replace(line, buffer);
	}
	wildcards = ft_split(line, '\n');
	free(line);
	if (ft_tablen_wc(cmd[j], wildcards) == 0)
	{
		free_tab(wildcards);
		return (cmd);
	}
	new_cmd = (char **)malloc(sizeof(char *) * (ft_tablen(cmd) - 1
				+ ft_tablen_wc(cmd[j], wildcards) + 1));
	ft_fill_new_tab(new_cmd, cmd, wildcards, j);
	return (new_cmd);
}

char	**ft_replace_cmd_wilds(char **cmd, int i, t_env *env)
{
	pid_t	pid;
	int		fd[2];
	char	**ls;
	char	**new_cmd;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ls = malloc(sizeof(char *) * 2);
		ls[0] = ft_strdup("ls");
		ls[1] = NULL;
		close(fd[1]);
		ft_child(ls, env->env);
	}
	waitpid(pid, NULL, 0);
	close(fd[1]);
	dup2(fd[0], 0);
	new_cmd = ft_malloc_new_tab(fd[0], cmd, i);
	close(fd[0]);
	return (new_cmd);
}

char	**ft_check_wildcards(char **cmd, t_env *env)
{
	int		i;
	char	**ptr;

	i = 0;
	if (!(*cmd) || !cmd)
		return (NULL);
	ptr = ft_tabdup(cmd);
	if (ft_check_buildins_out_echo(ft_strdup(cmd[0])))
		return (ptr);
	while (ptr[i])
	{
		if (ft_check_star(ptr[i]) && (ptr[i][0] != '\'' && ptr[i][0] != '\"'))
		{
			ptr = ft_replace_cmd_wilds(ptr, i, env);
			dup2(0, 0);
			dup2(1, 1);
			if (!ft_check_star(ptr[i]))
				i = 0;
		}
		i++;
	}
	return (ptr);
}
