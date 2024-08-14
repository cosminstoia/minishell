/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:13:28 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/13 19:24:38 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// If there is an infile, the function changes the fd of the infile to 0(stdin)
int	ft_handle_infile(t_token *tok, t_cnst *consts, int in_fd)
{
	int	i;

	i = 0;
	while (tok->in[i])
	{
		in_fd = open(tok->in[i], O_RDONLY, 0644);
		if (in_fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tok->in[i]);
			consts->exit_code = 1;
			return (0);
		}
		if (dup2(in_fd, STDIN_FILENO) < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tok->in[i]);
			consts->exit_code = 1;
			close(in_fd);
			return (0);
		}
		close(in_fd);
		i++;
	}
	return (1);
}

// If there is an outfile,
// the function changes the fd of the outfile to 1(stdout)
int	ft_handle_outfile(t_token *tok, t_cnst *consts, int out_fd)
{
	int	i;

	i = 0;
	while (tok->out[i])
	{
		out_fd = open(tok->out[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tok->out[i]);
			consts->exit_code = 1;
			return (0);
		}
		if (dup2(out_fd, STDOUT_FILENO) < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tok->out[i - 1]);
			consts->exit_code = 1;
			close(out_fd);
			return (0);
		}
		close(out_fd);
		i++;
	}
	return (1);
}

// the function changes the fd of the outfile to 1(stdout)
int	ft_handle_append(t_token *tok, t_cnst *consts, int out_fd)
{
	out_fd = open(tok->out_a[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (out_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(tok->out_a[0]);
		consts->exit_code = 1;
		return (0);
	}
	if (dup2(out_fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(tok->out_a[0]);
		consts->exit_code = 1;
		close(out_fd);
		return (0);
	}
	close(out_fd);
	return (1);
}
