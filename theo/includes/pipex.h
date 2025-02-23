/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:54:55 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/23 13:35:24 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

typedef struct s_args
{
	char	*path;
	char	**cmd;
	char	**env;
}		t_args;

typedef struct s_env
{
	char	**av;
	char	**env;
	int		status;
}			t_env;

char	*ft_getenv(char *name, char **env);
char	*ft_getpath(char *name, char **path);
char	*ft_strjoin_pipex(char const *s1, char const *s2, char *sep);
char	*ft_strcat_pipex(char *dest, char *src);
int		ft_open(char *name, int rw);
char	*ft_findname(char *name);
void	ft_free_tab(char **tab);
void	ft_manage_pipe(char **cmd, char **env);
void	ft_child(char **cmd, char **env);

#endif
