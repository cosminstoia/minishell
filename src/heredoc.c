/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:15:48 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/31 17:33:48 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_write(int in_fd, char *input)
{
	int	len;

	len = 0;
	len = ft_strlen(input);
	write(in_fd, input, len);
	write(in_fd, "\n", 1);
}

static void	ft_fd(int in_fd)
{
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		perror("dup2 input");
		close(in_fd);
	}
	close(in_fd);
	if (unlink("heredoc") < 0)
		perror("unlink heredoc");
	g_got_sig = 0;
}

static void	ft_unlink(void)
{
	if (unlink("heredoc") < 0)
		perror("unlink heredoc");
}

void	ft_handle_heredoc(t_token *tok, int in_fd)
{
	char	*input;

	ft_handle_sig_heredoc();
	in_fd = open("heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (in_fd < 0)
		perror("open input file");
	while (1)
	{
		input = readline("> ");
		if (g_got_sig)
		{
			g_got_sig = 0;
			ft_unlink();
			return ;
		}
		if (!input || (!ft_strncmp(input, tok->heredoc,
					ft_strlen(tok->heredoc))))
		{
			ft_unlink();
			return ;
		}
		ft_write(in_fd, input);
	}
	ft_fd(in_fd);
}
