/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:57:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/12 19:25:58 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	**split_line(char *line)
{
	int	buffer
}


void	loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		printf("Minishell$ ");
		line = readline();
		args = split_line(line);
		status = dash_execute(args);
		free(line);
		free(args);
	}
}


int	main(void)
{
	loop();
	return 0;
}
