/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/13 19:09:24 by gstronge         ###   ########.fr       */
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
	while (index < consts->tok_num)
	{
		waitpid(tok[index].pid, &status, 0);
		if (WIFEXITED(status))
			consts->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			consts->exit_code = 128 + WTERMSIG(status);
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

void	ft_handle_red_no_arg(t_token *tok, t_cnst *consts, int index)
{
	int	fd;
	int	i;

	i = 0;
	if (tok->out != NULL)
	{
		while (tok->out[i])
		{
			fd = open(tok->out[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(tok->out[i]);
				consts->exit_code = 1;
				return ;
			}
			i++;
		}
	}
	i = 0;
	if (tok->out_a != NULL)
	{
		while (tok->out_a[i])
		{
			fd = open(tok->out_a[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(tok->out_a[0]);
				consts->exit_code = 1;
				return ;
			}
			i++;
		}
	}
	i = 0;
	fd = 0;
	if (tok->in != NULL)
	{
		while (tok->in[i])
		{
			fd = open(tok->in[i], O_RDONLY, 0644);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(tok->in[i]);
				consts->exit_code = 1;
				return ;
			}
			i++;
		}
	}
	if (tok->heredoc != NULL)
		ft_handle_heredoc(tok, consts, fd, index);
}
