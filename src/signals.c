/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:59:52 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/28 15:27:34 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	got_sig = 0;

static void	ft_handle_sigint(int signum)
{
	write(1, "\n", 1);      // Print newline to move to a new line
	rl_on_new_line();       // Move readline to a new line
	rl_replace_line("", 0); // Clear the current input line in readline
	rl_redisplay();         // Redisplay the prompt
	got_sig = signum;
}

void	ft_handle_sig(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_sigint);
}
