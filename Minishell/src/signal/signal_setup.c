/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:59:37 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/15 10:43:51 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

volatile sig_atomic_t	g_signal;

void	ft_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}

void	setup_signal_handlers(void)
{
	enable_echoctl();
	ft_signal(SIGINT, sigint_handler_main);
	ft_signal(SIGQUIT, SIG_IGN);
}

void	child_signals(void)
{
	ft_signal(SIGINT, sigint_handler_child);
	ft_signal(SIGQUIT, sigquit_handler_child);
}

void	ignore_signals(void)
{
	ft_signal(SIGINT, SIG_IGN);
	ft_signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
	ft_signal(SIGINT, sigint_handler_heredoc);
	ft_signal(SIGQUIT, SIG_IGN);
	ft_signal(SIGSEGV, SIG_IGN);
}
