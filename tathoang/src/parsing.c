/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/12 19:25:46 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_quote(char *input)
{
	int		i;
	int		start = 0;
	int		end = 0;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
		{
			i++;
			while ((input[i]) && input[i] != '"')
				i++;
		}

	}
}


