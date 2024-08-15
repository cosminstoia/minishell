/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/15 17:19:46 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unlink(t_token *tok, t_cnst *consts, int index)
{
	if (unlink("heredoc") < 0)
	{
		perror(tok[index].heredoc[0]);
		consts->exit_code = 0;
	}
}

/* Function used to wait for the child process
with pid tok[index].pid to complete */
void	ft_wait(t_token *tok, t_cnst *consts)
{
	int	status;
	int	index;

	index = 0;
	status = 0;
	while (index < consts->tok_num)
	{
		if (tok[index].cmd && tok[index].path)
		{
			waitpid(tok[index].pid, &status, 0);
			if (WIFEXITED(status))
				consts->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				consts->exit_code = 128 + WTERMSIG(status);
		}
		if (tok[index].heredoc)
			ft_unlink(tok, consts, index);
		index++;
	}
}

void	ft_execute_child(t_token *tok, t_cnst *consts, int index)
{
	if (!tok[index].path)
		exit(EXIT_FAILURE);
	if (execve(tok[index].path, tok[index].cmd, consts->environ) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
