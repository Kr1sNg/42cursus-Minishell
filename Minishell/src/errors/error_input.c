/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/03 19:36:44 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error_syntax(char *s)
{
	printf("Minishell: syntax error near unexpected token `%s'\n", s);
	//exit(EXIT_FAILURE);
}

void	ft_error_input(int er)
{
	if (er == -42)
		printf("syntax error\n");
	//exit(EXIT_FAILURE);
}
