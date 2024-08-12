/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:58:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/12 13:42:13 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_handle_input_redirection(t_token *tok, t_cnst *consts,
		int *pipefd, int index)
{
	int	inflag;

	inflag = 0;
	if (tok->in)
	{
		if (ft_handle_infile(tok, consts, pipefd[0]))
			inflag = 1;
		else
			return (0);
	}
	if (tok->heredoc)
	{
		if (ft_handle_heredoc(tok, consts, pipefd[0]))
			inflag = 1;
		else
			return (0);
	}
	if (!inflag && index > 0)
	{
		dup2(tok->input_fd, STDIN_FILENO);
		close(tok->input_fd);
	}
	return (1);
}

static int	ft_handle_output_redirection(t_token *tok, t_cnst *consts,
		int *pipefd, int index)
{
	int	outflag;

	outflag = 0;
	if (tok->out)
	{
		if (ft_handle_outfile(tok, consts, pipefd[1]))
			outflag = 1;
		else
			return (0);
	}
	if (tok->out_a)
	{
		if (ft_handle_append(tok, consts, pipefd[1]))
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
