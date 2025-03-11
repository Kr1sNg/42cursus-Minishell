/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/11 14:38:24 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	ft_error_syntax(char *s)
{
	printf("minishell: syntax error near unexpected token `%s'\n", s);
}

void	ft_error_input(int er)
{
	(void)er;
	return ;
	// if (er == -42)
		// printf("syntax error\n");
	//exit(EXIT_FAILURE);
}

void	ft_error_target(char *s)
{
	char	*access;
	
	access = ft_strjoin("bash: ", s);
	perror(access);
	free(access);
}