/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:12:56 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/11 13:44:18 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/libraries.h"

// int	ft_strlen_wildcards(char *str)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != '*')
// 			len++;
// 		i++;
// 	}
// 	return(len);
// }

// int	ft_check_star(char * str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '*')
// 			return(1);
// 		i++;
// 	}
// 	return(0);
// }

// char	*ft_replace_cmd_only(char *cmd)
// {
// 	int		len;
// 	char	*dest;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen_wildcards(cmd);
// 	dest = (char *)malloc((len + 1) * sizeof(char));
// 	while (i < len)
// 	{
// 		if (cmd[i] == '*')
// 			i++;
// 		else
// 		{
// 			dest[j] = cmd[i]; 
// 			i++;
// 			j++;
// 		}
// 	}
// 	dest[j] = '\0';
// 	return(dest);
// }

// char	**ft_replace_cmd_wilds(char **cmd, int i, t_env *env)
// {
// 	pid_t	pid;
// 	int		fd[2];
// 	char	**ls;
// 	char	**new_cmd;

// 	pipe(fd);
// 	dup2(fd[1], 1);
// 	dup2(fd[0], 0);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(fd[1]);
// 		ls = malloc(sizeof(char *) * 2);
// 		ls[0] = ft_strdup("ls");
// 		ls[1] = NULL;
// 		ft_child(ls, env);
// 		close(fd[0]);
// 	}
// 	wait(NULL);
// 	close(fd[0]);
// 	new_cmd = ft_();
// 	close(fd[1]);
// 	return (new_cmd);
// }

// void	ft_check_wildcards(char **cmd, t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if (ft_check_star(cmd[i]))
// 		{
// 			if (cmd[i][0] == '*' && !cmd[i][1])
// 			{
// 				cmd = ft_replace_cmd_wilds(cmd, i, env);
// 				i = 0;
// 			}
// 			else
// 				cmd[i] = ft_replace_cmd_only(cmd[i]);
// 		}
// 		i++;
// 	}
// }