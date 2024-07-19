/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:59:52 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/19 18:32:47 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			got_sig = 0;

static void	ft_handle_sigint(int signum)
{
	write(1, "\n", 1);      // Print newline to move to a new line
	rl_on_new_line();       // Move readline to a new line
	rl_replace_line("", 0); // Clear the current input line in readline
	rl_redisplay();         // Redisplay the prompt
	got_sig = signum;       // Set the signal flag
}

void	ft_handle_sig(void)
{
	rl_catch_signals = 0;             // Disable readline's signal handling
	signal(SIGQUIT, SIG_IGN);         // Ignore SIGQUIT (CTRL+\)
	signal(SIGINT, ft_handle_sigint); // Handle SIGINT (CTRL+C)
}

static void	ft_handle_sigint_heredoc(int signum)
{
	if (signum == SIGINT)
		got_sig = 1; // Set the signal flag
}

void	ft_handle_sig_heredoc(void)
{
	rl_catch_signals = 0;
	// Disable readline's signal handling
	signal(SIGQUIT, SIG_IGN);                 // Ignore SIGQUIT (CTRL+\)
	signal(SIGINT, ft_handle_sigint_heredoc); // Handle SIGINT (CTRL+C)
   // return(got_sig);
}
