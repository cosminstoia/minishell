/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:13:28 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/15 16:45:57 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// If there is an infile, the function changes the fd of the infile to 0(stdin)
int	ft_handle_infile(t_token *tok, t_cnst *consts, int in_fd, int index)
{
	int	i;

	i = 0;
	while (tok[index].in[i])
	{
		if (i > 0)
			close(in_fd);
		in_fd = open(tok[index].in[i], O_RDONLY, 0644);
		if (in_fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tok[index].in[i]);
			consts->exit_code = 1;
			return (0);
		}
		if (tok[index].cmd != NULL)
		{
			if (dup2(in_fd, STDIN_FILENO) < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(tok[index].in[i]);
				consts->exit_code = 1;
				close(in_fd);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

// If there is an outfile,
// the function changes the fd of the outfile to 1(stdout)
int	ft_handle_outfile(t_token *tok, t_cnst *consts, int out_fd, int index)
{
	int	i;

	i = 0;
	while (tok[index].out[i])
	{
		if (i > 0)
			close(out_fd);
		out_fd = open(tok[index].out[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tok[index].out[i]);
			consts->exit_code = 1;
			return (0);
		}
		if (tok[index].cmd != NULL)
		{
			if (dup2(out_fd, STDOUT_FILENO) < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(tok[index].out[i]);
				consts->exit_code = 1;
				close(out_fd);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

// the function changes the fd of the outfile to 1(stdout)
int	ft_handle_append(t_token *tok, t_cnst *consts, int out_fd, int index)
{
	int	i;

	i = 0;
	while (tok[index].out_a[i])
	{
		if (i > 0)
			close(out_fd);
		out_fd = open(tok[index].out_a[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tok[index].out_a[i]);
			consts->exit_code = 1;
			return (0);
		}
		if (tok[index].cmd != NULL)
		{
			if (dup2(out_fd, STDOUT_FILENO) < 0)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(tok[index].out_a[i]);
				consts->exit_code = 1;
				close(out_fd);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
