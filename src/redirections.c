/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:58:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/24 09:58:31 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If there is an infile, the function changes the fd of the infile to 0(stdin)
static void	ft_handle_infile(t_token *tok, int in_fd)
{
	in_fd = open(tok->in, O_RDONLY);
	if (in_fd < 0)
	{
		perror("open input file");
		exit(EXIT_FAILURE);
	}
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(in_fd);
		exit(EXIT_FAILURE);
	}
	close(in_fd);
}

// If there is an outfile,
// the function changes the fd of the outfile to 1(stdout)
static void	ft_handle_outfile(t_token *tok, int out_fd)
{
	out_fd = open(tok->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
	{
		perror("open output file");
		exit(EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output");
		close(out_fd);
		exit(EXIT_FAILURE);
	}
	close(out_fd);
}

// the function changes the fd of the outfile to 1(stdout)
static void	ft_handle_append(t_token *tok, int out_fd)
{
	out_fd = open(tok->out_a, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
	{
		perror("open append output file");
		exit(EXIT_FAILURE);
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 append output");
		close(out_fd);
		exit(EXIT_FAILURE);
	}
	close(out_fd);
}

void	ft_redirect(t_token *tok)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (tok->in)
		ft_handle_infile(tok, in_fd);
	if (tok->out)
		ft_handle_outfile(tok, out_fd);
	else if (tok->out_a)
		ft_handle_append(tok, out_fd);
	return ;
}
