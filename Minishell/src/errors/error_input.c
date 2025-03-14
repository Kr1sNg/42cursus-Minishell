/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 16:45:25 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	ft_error_syntax(char *s, t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		i = 0;
	else
		i = token->print_error_syntax;
	if (i == 0)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", s);
		if (token)
			(token->print_error_syntax)++;
	}
}

void	ft_error_target(char *s)
{
	printf("minishell: %s: No such file or directory\n", s);
}
