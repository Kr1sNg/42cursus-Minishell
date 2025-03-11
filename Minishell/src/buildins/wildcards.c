/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:12:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/11 16:23:20 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_strlen_wildcards(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '*')
			len++;
		i++;
	}
	return(len);
}

int	ft_double_tab_len(char **str)
{
	int	i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}

int	ft_check_star(char * str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return(1);
		i++;
	}
	return(0);
}

char	*ft_replace_cmd_only(char *cmd)
{
	int		len;
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen_wildcards(cmd);
	dest = (char *)malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		if (cmd[i] == '*')
			i++;
		else
		{
			dest[j] = cmd[i]; 
			i++;
			j++;
		}
	}
	dest[j] = '\0';
	return(dest);
}

void	ft_fill_new_tab(char **new_cmd, char **cmd, char **wildcards, int j)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while(cmd[k])
	{
		if (k != j)
		{
			new_cmd[i] = cmd[k];
			i++;
		}
		k++;
	}
	k = 0;
	while(wildcards[k])
	{
		new_cmd[i] = wildcards[k];
		i++;
		k++;
	}
	new_cmd[i] = NULL;
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
	while(buffer || i++ == 0)
	{
		if (buffer)
			free(buffer);
		buffer = get_next_line(fd);
		line = ft_strjoin(line, buffer);
	}
	wildcards = ft_split(line, '\n');
	new_cmd = (char **)malloc(sizeof(char *) * (ft_double_tab_len(cmd) - 1
			+ ft_double_tab_len(wildcards) + 1));
	ft_fill_new_tab(new_cmd, cmd, wildcards, j);
	free(wildcards);
	free(line);
	return(new_cmd);
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
		ft_child(ls, env->env);
		close(fd[1]);
	}
	wait(NULL);
	close(fd[1]);
	dup2(fd[0], 0);
	new_cmd = ft_malloc_new_tab(fd[0], cmd, i);
	close(fd[0]);
	return (new_cmd);
}

void	ft_check_wildcards(char **cmd, t_env *env)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_check_star(cmd[i]))
		{
			if (cmd[i][0] == '*' && !cmd[i][1])
			{
				cmd = ft_replace_cmd_wilds(cmd, i, env);
				i = 0;
			}
			else
				cmd[i] = ft_replace_cmd_only(cmd[i]);
		}
		i++;
	}
}