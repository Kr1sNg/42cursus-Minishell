/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:59:37 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 14:56:27 by tat-nguy         ###   ########.fr       */
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
	ft_signal(SIGINT, sigint_handler);
	ft_signal(SIGQUIT, SIG_IGN);
}

// void	ft_signal_child(void)
// {
// 	ft_signal(SIGINT, sigint_quit);
// 	ft_signal(SIGQUIT, sigquit_handler);
// }

// void	ft_signal_input(void)
// {
// 	ft_signal(SIGINT, sigint_prompt);
// 	ft_signal(SIGQUIT, SIG_IGN);
// }

// void	setup_signal_handlers(void)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;
	
// 	sa_int.sa_handler = sigint_handler;
// 	sigemptyset(&sa_int.sa_mask);
// 	sa_int.sa_flags = SA_RESTART;
// 	sigaction(SIGINT, &sa_int, NULL);

// 	sa_quit.sa_handler = SIG_IGN;
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_quit.sa_flags = SA_RESTART;
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }

void	restore_default_signals(void)
{
	ft_signal(SIGINT, SIG_DFL);
	ft_signal(SIGQUIT, sigquit_handler);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
	signal(EOF, SIG_IGN);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

// void	setup_signal_handlers(void);
// void	restore_default_signals(void);
// void	ignore_signals(void);
// void	sigint_handler(int signum);
// void	sigquit_handler(int signum);

