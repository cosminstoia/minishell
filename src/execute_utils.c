/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/08 15:51:28 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Function used to wait for the child process
with pid tok[index].pid to complete */
void	ft_wait(t_token *tok, t_cnst *consts)
{
	int	status;
	int	index;

	index = 0;
	while (index < consts->tok_num)
	{
		waitpid(tok[index].pid, &status, 0);
		if (WIFEXITED(status))
			tok->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			tok->exit_code = 128 + WTERMSIG(status);
		index++;
	}
}

void	ft_execute_child(t_token *tok, t_cnst *consts, int index, int pipefd[2])
{
	tok[index].cmd = ft_expand_dollar(tok, consts, &tok[index]);
	tok[index].cmd = ft_remove_quotes(tok[index].cmd);
	if (index > 0)
	{
		dup2(tok[index].input_fd, STDIN_FILENO);
		close(tok[index].input_fd);
	}
	if (index < consts->tok_num - 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	tok[index].path = ft_make_path(tok, consts, index);
	execve(tok[index].path, tok[index].cmd, consts->environ);
}

/* Close input_fd if not the first command
Close pipefd[1] and update input_fd if not the last command */
void	ft_execute_parent(t_token *tok, int index, int pipefd[2],
		t_cnst *consts)
{
	if (index > 0)
		close(tok[index].input_fd);
	if (index < consts->tok_num - 1)
	{
		close(pipefd[1]);
		tok[index + 1].input_fd = pipefd[0];
	}
}

void	ft_handle_red_no_arg(t_token *tok, t_cnst *consts, int index)
{
	int	fd;

	fd = 0;
	if (tok[index].cmd[0] == NULL)
	{
		if (tok->out != NULL)
			fd = open(tok->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tok->out_a != NULL)
			fd = open(tok->out_a, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tok->heredoc != NULL)
			ft_handle_heredoc(tok, consts, fd);
		else if (tok->in != NULL)
		{
			fd = open(tok->in, O_RDONLY, 0644);
			if (fd < 0)
			{
				printf("minishell: %s: No such file or directory\n",
					tok[index].in);
				return ;
			}
		}
	}
}
