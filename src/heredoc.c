/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:15:48 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/15 20:07:20 by cstoia           ###   ########.fr       */
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

static void	ft_fd(t_token *tok, t_cnst *consts, int in_fd, int index)
{
	if (dup2(in_fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(tok[index].heredoc[0]);
		consts->exit_code = 1;
	}
	g_got_sig = 0;
}

static int	ft_heredoc_utils(t_token *tok, int in_fd, int index)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		ft_handle_sig_heredoc();
		if (!input || (!ft_strncmp(input, tok[index].heredoc[0],
					ft_strlen(tok[index].heredoc[0]))))
			return (1);
		ft_write(in_fd, input);
	}
}

static char	**ft_heredoc_cmd(t_token *tok, t_cnst *consts, int index)
{
	char	**new_cmd;
	int		cmd_no;

	cmd_no = 0;
	while (tok[index].cmd[cmd_no])
		cmd_no++;
	new_cmd = (char **)malloc((cmd_no + 2) * sizeof(char *));
	if (new_cmd == NULL)
		ft_cleanup(tok, consts, errno);
	cmd_no = 0;
	while (tok[index].cmd[cmd_no])
	{
		new_cmd[cmd_no] = tok[index].cmd[cmd_no];
		cmd_no++;
	}
	new_cmd[cmd_no] = ft_strdup("heredoc");
	new_cmd[cmd_no + 1] = NULL;
	free(tok[index].cmd);
	return (new_cmd);
}

int	ft_handle_heredoc(t_token *tok, t_cnst *consts, int in_fd, int index)
{
	int	saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	in_fd = open("heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (in_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(tok[index].heredoc[0]);
		consts->exit_code = 1;
		return (0);
	}
	ft_heredoc_utils(tok, in_fd, index);
	ft_fd(tok, consts, in_fd, index);
	if (tok[index].cmd && (!ft_strncmp("cat", tok[index].cmd[0], 4)
			|| !ft_strncmp("grep", tok[index].cmd[0], 5) || !ft_strncmp("awk",
				tok[index].cmd[0], 4)))
		tok[index].cmd = ft_heredoc_cmd(tok, consts, index);
	dup2(saved_stdin, STDIN_FILENO);
	return (1);
}
