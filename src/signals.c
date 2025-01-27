/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:59:52 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/12 23:01:13 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			g_got_sig = 0;

static void	ft_handle_sigint(int signum)
{
	struct termios	term;

	(void)signum;
	tcgetattr(STDIN_FILENO, &term);
	if ((term.c_lflag & ICANON))
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_got_sig = signum;
}

static void	ft_handle_sigquit(int signum)
{
	struct termios	term;

	(void)signum;
	tcgetattr(STDIN_FILENO, &term);
	if ((term.c_lflag & ICANON))
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	ft_handle_sig(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, ft_handle_sigquit);
	signal(SIGINT, ft_handle_sigint);
}

static void	ft_handle_sigint_heredoc(int signum)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (signum == SIGINT)
		g_got_sig = 1;
}

void	ft_handle_sig_heredoc(void)
{
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_sigint_heredoc);
}
