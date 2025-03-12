/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:58:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/12 15:05:30 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	ft_error_syntax(char *s)
{
	printf("minishell: syntax error near unexpected token `%s'\n", s);
}

void	ft_error_target(char *s)
{
	printf("minishell: %s: No such file or directory\n", s);
}