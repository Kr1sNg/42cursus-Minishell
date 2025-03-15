/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:59:37 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/15 12:19:02 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

/* handler in main */

void	ft_sigint_main(t_env *infos)
{
	g_signal = 0;
	infos->status = 130;
	rl_reset_terminal(NULL);
}

void	sigint_handler_main(int signum)
{
	(void)signum;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/* handler in cat, sleep 42, grep... */
void	sigquit_handler_child(int signum)
{
	(void)signum;
	// g_signal = SIGQUIT;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(131);
}

void	sigint_handler_child(int signum)
{
	(void)signum;
	// g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(130);
}

/* handler in heredoc */
void	sigint_handler_heredoc(int signum)
{
	(void)signum;
	// g_signal = SIGINT;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	exit(130);
}
