/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:58:20 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/19 17:53:45 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// If there is an infile, the function changes the fd of the infile to 0(stdin)
static void	ft_handle_infile(t_token *tok, int in_fd)
{
	in_fd = open(tok->in, O_RDONLY, 0644);
	if (in_fd < 0)
	{
		perror("open input file");
	}
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(in_fd);
	}
	close(in_fd);
}

// If there is an outfile,
// the function changes the fd of the outfile to 1(stdout)
static void	ft_handle_outfile(t_token *tok, int out_fd)
{
	out_fd = open(tok->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (out_fd < 0)
		perror("open output file");
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 output");
		close(out_fd);
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
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		perror("dup2 append output");
		close(out_fd);
	}
	close(out_fd);
}

// If there is a heredoc, the function reads the lines of user input until the
// delimeter is reached, then changes the fd of the heredoc to 0(stdin)
void	ft_handle_heredoc(t_token *tok, int in_fd)
{
	char	*input;
	int		len;

	ft_handle_sig_heredoc();
	in_fd = open("heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (in_fd < 0)
		perror("open input file");
	while (1)
	{
		input = readline("> ");
		if(got_sig)
		{
			got_sig = 0;
			if (unlink("heredoc") < 0)
				perror("unlink heredoc");
			return ;
		}
		if (!input || (!ft_strncmp(input, tok->heredoc, ft_strlen(tok->heredoc))))
		{
			if (unlink("heredoc") < 0)
				perror("unlink heredoc");
			return ;
		}
		len = 0;
		len = ft_strlen(input);
		write(in_fd, input, len);
		write(in_fd, "\n", 1);
	}
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(in_fd);
	}
	close(in_fd);
	if (unlink("heredoc") < 0)
		perror("unlink heredoc");
	got_sig = 0;
}

int	ft_redirect(t_token *tok, int out_fd)
{
	int	in_fd;

	in_fd = -1;
	if (tok->in)
	{
		ft_handle_infile(tok, in_fd);
		return (0);
	}
	else if (tok->heredoc)
	{
		ft_handle_heredoc(tok, in_fd); // need to fugure this out, bash does some weird things if there is a heredoc and an infile !return (0);
		return(0);
	}
	else if (tok->out)
	{
		ft_handle_outfile(tok, out_fd);
		return (0);
	}
	else if (tok->out_a)
	{
		ft_handle_append(tok, out_fd);
		return (0);
	}
	else
		return (1);
}
