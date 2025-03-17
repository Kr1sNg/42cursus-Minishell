/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 23:52:51 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/17 18:14:07 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

static void	input_heredoc(char *eof, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strncmp(line, eof, ft_strlen(eof))
			&& line[ft_strlen(eof)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

int	ft_here_doc(char *eof)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		disable_echoctl();
		heredoc_signals();
		close(fd[0]);
		input_heredoc(eof, fd[1]);
		close(fd[1]);
		enable_echoctl();
		exit(0);
	}
	ignore_signals();
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}
