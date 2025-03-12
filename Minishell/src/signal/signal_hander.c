/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:59:37 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/12 22:20:52 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

void	sigint_prompt(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// g_signal_value = signum;
}

void	sigquit_handler(int signum)
{
	g_signal_value = signum;
	write(1, "Quit\n", 5);
	exit(131);
}

void	sigint_quit(int signum)
{
	// g_signal_value = signum;
	(void)signum;
	// write(1, "QQQQQ", 5);
	// rl_on_new_line();
	exit(131);
}