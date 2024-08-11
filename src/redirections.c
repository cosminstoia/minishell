/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:58:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/11 16:36:30 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// If there is an infile, the function changes the fd of the infile to 0(stdin)
static int	ft_handle_infile(t_token *tok, t_cnst *consts, int in_fd)
{
	in_fd = open(tok->in, O_RDONLY, 0644);
	if (in_fd < 0)
	{
		perror(tok->in);
		consts->exit_code = 1;
		return (0);
	}
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		perror(tok->in);
		consts->exit_code = 1;
		close(in_fd);
		return (0);
	}
	close(in_fd);
	return (1);
}

// If there is an outfile,
// the function changes the fd of the outfile to 1(stdout)
static int	ft_handle_outfile(t_token *tok, t_cnst *consts, int out_fd)
{
	out_fd = open(tok->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror(tok->out);
		consts->exit_code = 1;
		return (0);
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror(tok->out);
		consts->exit_code = 1;
		close(out_fd);
		return (0);
	}
	close(out_fd);
	return (1);
}

// the function changes the fd of the outfile to 1(stdout)
static int	ft_handle_append(t_token *tok, t_cnst *consts, int out_fd)
{
	out_fd = open(tok->out_a, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
	{
		perror(tok->out_a);
		consts->exit_code = 1;
		return (0);
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror(tok->out_a);
		consts->exit_code = 1;
		close(out_fd);
		return (0);
	}
	close(out_fd);
	return (1);
}

int	ft_redirect(t_token *tok, t_cnst *consts, int *pipefd, int index)
{
	int	inflag;
	int	outflag;

	inflag = 0;
	outflag = 0;	
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
	if (!inflag && index > 0)
	{
		dup2(tok->input_fd, STDIN_FILENO);
		close(tok->input_fd);
	}
	if (!outflag && index < consts->tok_num - 1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		// close(pipefd[1]);
	}
	return (1);
}
