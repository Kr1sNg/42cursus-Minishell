/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/13 13:10:21 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

// char	**split_line(char *line)
// {
// 	int	buffer
// }


// void	loop(void)
// {
// 	char	*line;
// 	char	**args;
// 	int		status;

// 	status = 1;
// 	while (status)
// 	{
// 		printf("Minishell$ ");
// 		line = readline();
// 		args = split_line(line);
// 		status = dash_execute(args);
// 		free(line);
// 		free(args);
// 	}
// }

void	handler(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

int	main(void)
{
	static char	*input;

	input = (char *)NULL;
	while (1)
	{
		input = readline("minishell:~ $ ");
		if (!input)
			break ;
		add_history(input);
		printf("\n\n\t%s\n", input);
		signal(SIGINT, handler);
		// signal(SIGQUIT, SIG_IGN); //SIG_IGN: ignore signal
		// signal(SIGTSTP, SIG_IGN); // SIGTSTP: keyboard stop = EOF
	}
	return (0);
}
