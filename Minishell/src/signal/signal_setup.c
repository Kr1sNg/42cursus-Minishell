/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:59:37 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/12 22:08:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libraries.h"

sig_atomic_t	g_signal_value;

void	ft_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;
	
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(signum, &sa, NULL);
}

void	ft_signal_main(void)
{
	ft_signal(SIGINT, SIG_IGN);
	ft_signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_child(void)
{
	ft_signal(SIGINT, sigint_quit);
	ft_signal(SIGQUIT, sigquit_handler);
}

void	ft_signal_input(void)
{
	ft_signal(SIGINT, sigint_prompt);
	ft_signal(SIGQUIT, SIG_IGN);
}
