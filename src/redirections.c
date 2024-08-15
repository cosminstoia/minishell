/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:58:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/15 21:43:21 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_handle_input_redirection(t_token *tok, t_cnst *consts,
		int *pipefd, int index)
{
	int	inflag;

	inflag = 0;
	if (tok[index].in)
	{
		if (ft_handle_infile(tok, consts, pipefd[0], index))
			inflag = 1;
		else
			return (0);
	}
	if (tok[index].heredoc)
	{
		if (ft_handle_heredoc(tok, consts, pipefd[0], index))
			inflag = 1;
		else
			return (0);
	}
	if (!inflag && index > 0 && tok[index].cmd != NULL)
		dup2(tok[index].input_fd, STDIN_FILENO);
	return (1);
}

static int	ft_handle_output_redirection(t_token *tok, t_cnst *consts,
		int *pipefd, int index)
{
	int	outflag;

	outflag = 0;
	if (tok[index].out)
	{
		if (ft_handle_outfile(tok, consts, pipefd[1], index))
			outflag = 1;
		else
			return (0);
	}
	if (tok[index].out_a)
	{
		if (ft_handle_append(tok, consts, pipefd[1], index))
			outflag = 1;
		else
			return (0);
	}
	if (!outflag && index < consts->tok_num - 1)
		dup2(pipefd[1], STDOUT_FILENO);
	return (1);
}

int	ft_redirect(t_token *tok, t_cnst *consts, int *pipefd, int index)
{
	if (!ft_handle_input_redirection(tok, consts, pipefd, index))
		return (0);
	if (!ft_handle_output_redirection(tok, consts, pipefd, index))
		return (0);
	return (1);
}
