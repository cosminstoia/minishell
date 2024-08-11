/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:13:28 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/11 18:15:45 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// If there is an infile, the function changes the fd of the infile to 0(stdin)
int	ft_handle_infile(t_token *tok, t_cnst *consts, int in_fd)
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
int	ft_handle_outfile(t_token *tok, t_cnst *consts, int out_fd)
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
int	ft_handle_append(t_token *tok, t_cnst *consts, int out_fd)
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
