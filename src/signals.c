/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:59:52 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/24 10:00:25 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	got_sig = 0;

void	ft_handle_sig(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();       // Move readline to a new line
		rl_replace_line("", 0); // Clear the current input line in readline
		printf("\n");           // Print newline to move to a new line
		rl_redisplay();         // Redisplay the prompt
		got_sig = 1;
		return ;
	}
}