/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:49:14 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/15 16:40:48 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_pipes_and_handle_errors(t_cnst *consts, int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		consts->exit_code = 1;
		exit(EXIT_FAILURE);
	}
}

static void	execute_single_builtin(t_token *tok, t_cnst *consts, int index, int *pipefd)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (ft_redirect(tok, consts, pipefd, index))
		ft_execute_builtins(tok, consts, index, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
}

static void	execute_non_builtin(t_token *tok, t_cnst *consts, int index, int *pipefd)
{
	tok[index].cmd = ft_expand_dollar(tok, consts, &tok[index]);
	tok[index].cmd = ft_remove_quotes(tok[index].cmd);
	tok[index].path = ft_make_path(tok, consts, index);
	if (tok[index].path)
	{
		tok[index].pid = fork();
		if (tok[index].pid == 0)
		{
			if (ft_redirect(tok, consts, pipefd, index))
			{
				close(pipefd[0]);
				close(pipefd[1]);
				if (ft_is_builtin(tok[index].cmd[0]))
				{
					ft_execute_builtins(tok, consts, index, STDOUT_FILENO);
					exit(EXIT_SUCCESS);
				}
				else
					ft_execute_child(tok, consts, index);
			}
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_execute(t_token *tok, t_cnst *consts)
{
	int	pipefd[2];
	int	index;

	pipefd[0] = -1;
	pipefd[1] = -1;	
	index = 0;
	while (index < consts->tok_num)
	{
		if (tok[index].cmd == NULL || !(consts->tok_num == 1 && ft_is_builtin(tok[index].cmd[0])))
		{
			setup_pipes_and_handle_errors(consts, pipefd);
			if (tok[index].cmd == NULL)
				ft_redirect(tok, consts, pipefd, index);
			else
				execute_non_builtin(tok, consts, index, pipefd);
			if (index > 0)
				close(tok[index].input_fd);
			if (index < consts->tok_num - 1)
				tok[index + 1].input_fd = dup(pipefd[0]);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		else
			execute_single_builtin(tok, consts, index, pipefd);
		index++;
	}
	ft_wait(tok, consts);
}
