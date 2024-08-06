/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:58:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/06 18:05:49 by cstoia           ###   ########.fr       */
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
static void	ft_handle_outfile(t_token *tok, t_cnst *consts, int out_fd)
{
	out_fd = open(tok->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror(tok->in);
		consts->exit_code = 1;
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror(tok->in);
		consts->exit_code = 1;
		close(out_fd);
	}
	close(out_fd);
}

// the function changes the fd of the outfile to 1(stdout)
static void	ft_handle_append(t_token *tok, t_cnst *consts, int out_fd)
{
	out_fd = open(tok->out_a, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
	{
		perror(tok->in);
		consts->exit_code = 1;
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror(tok->in);
		consts->exit_code = 1;
		close(out_fd);
	}
	close(out_fd);
}

int	ft_redirect(t_token *tok, t_cnst *consts, int out_fd)
{
	int	in_fd;
	int	flag;

	flag = 0;
	in_fd = -1;
	if (tok->in)
	{
		if (ft_handle_infile(tok, consts, in_fd))
			flag = 1;
		else
			return (-1);
	}
	if (tok->heredoc)
	{
		ft_handle_heredoc(tok, consts, in_fd);
		flag = 1;
	}
	if (tok->out)
	{
		ft_handle_outfile(tok, consts, out_fd);
		flag = 1;
	}
	if (tok->out_a)
	{
		ft_handle_append(tok, consts, out_fd);
		flag = 1;
	}
	return (flag);
}
