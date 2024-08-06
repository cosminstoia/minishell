/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:49:14 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/06 18:08:13 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	setup_pipes_and_handle_errors(t_token *tok, int *pipefd, int index,
		t_cnst *consts)
{
	if (index < consts->tok_num - 1)
	{
		if (pipe(pipefd) == -1)
		{
			perror(tok->in);
			consts->exit_code = 1;
			exit(EXIT_FAILURE);
		}
	}
}

static void	execute_builtin_command(t_token *tok, t_cnst *consts, int index,
		int *pipefd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	red;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	red = ft_redirect(&tok[index], consts, pipefd[1]);
	if (red && index < consts->tok_num - 1)
		ft_execute_builtins(tok, consts, index, pipefd[1]);
	else if (red != -1)
		ft_execute_builtins(tok, consts, index, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
}

static void	handle_child_process(t_token *tok, t_cnst *consts, int index,
		int *pipefd)
{
	if (ft_redirect(&tok[index], consts, pipefd[1]))
		return ;
	else
	{
		tok[index].pid = fork();
		if (tok[index].pid == 0)
		{
			ft_execute_child(tok, consts, index, pipefd);
			exit(EXIT_SUCCESS);
		}
		else
			ft_execute_parent(tok, index, pipefd, consts);
	}
}

void	ft_execute(t_token *tok, t_cnst *consts)
{
	int	pipefd[2];
	int	index;

	index = 0;
	while (index < consts->tok_num)
	{
		setup_pipes_and_handle_errors(tok, pipefd, index, consts);
		if (tok[index].cmd[0] == NULL)
		{
			ft_handle_red_no_arg(tok, consts, index);
			return ;
		}
		if (ft_is_builtin(tok[index].cmd[0]))
			execute_builtin_command(tok, consts, index, pipefd);
		else
			handle_child_process(tok, consts, index, pipefd);
		if (index < consts->tok_num - 1)
			tok[index + 1].input_fd = pipefd[0];
		close(pipefd[1]);
		index++;
	}
	ft_wait(tok, consts);
}
