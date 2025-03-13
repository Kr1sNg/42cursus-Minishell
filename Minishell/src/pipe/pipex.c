/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:52:51 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/13 14:28:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

int	ft_here_doc(char *eof)
{
	int		here_doc;
	char	*line;

	here_doc = ft_open("here_doc", APPEND);
	line = get_next_line(STDIN_FILENO);
	while (!(ft_strcmp(line, eof) == 10 && (ft_strlen(line) - 1 == ft_strlen(eof))))
	{
		ft_putstr_fd(line, here_doc);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(here_doc);
	here_doc = ft_open("here_doc", READ);
	return (here_doc);
}

// void	ft_no_here_doc(int ac, t_env en, int *file_out, int *file_in)
// {
// 	if (access(en.av[ac - 1], W_OK) == 0)
// 		unlink(en.av[ac - 1]);
// 	*file_out = ft_open(en.av[ac - 1], 1);
// 	*file_in = ft_open(en.av[1], 0);
// 	if (*file_in != -1)
// 		dup2(*file_in, 0);
// 	else if (access(en.av[1], F_OK) == 0)
// 		exit(0);
// }

// void	ft_select_pipe(int ac, t_env en)
// {
// 	int		i;
// 	int		file_in;
// 	int		file_out;

// 	if (ft_strcmp(en.av[1], "here_doc") == 0 && ac > 5)
// 	{
// 		i = 3;
// 		dup2(ft_here_doc(en), 0);
// 		file_out = ft_open(en.av[ac - 1], 2);
// 	}
// 	else
// 	{
// 		i = 2;
// 		ft_no_here_doc(ac, en, &file_out, &file_in);
// 	}
// 	while (i < ac - 2)
// 		ft_manage_pipe(en.av[i++], en);
// 	unlink("here_doc");
// 	if (file_out == -1)
// 		exit(1);
// 	dup2(file_out, 1);
// 	ft_child(en.av[i], en.env);
// }

// int	main(int ac, char **av, char **env)
// {
// 	t_env	envir;

// 	envir.av = av;
// 	envir.env = env;
// 	envir.status = 0;
// 	if (ac < 5)
// 		return (ft_printf(1, "not enough arguments\n"), 1);
// 	ft_select_pipe(ac, envir);
// 	return (0);
// }
