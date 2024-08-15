/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:13:28 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/15 20:47:05 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_dup_file_to_std(t_cnst *consts, int fd, char *filename, int std)
{
	if (dup2(fd, std) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		consts->exit_code = 1;
		close(fd);
		return (0);
	}
	return (1);
}

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
			if (!ft_dup_file_to_std(consts, in_fd, tok[index].in[i],
					STDIN_FILENO))
				return (0);
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
			if (!ft_dup_file_to_std(consts, out_fd, tok[index].out[i],
					STDOUT_FILENO))
				return (0);
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
			if (!ft_dup_file_to_std(consts, out_fd, tok[index].out_a[i],
					STDOUT_FILENO))
				return (0);
		}
		i++;
	}
	return (1);
}
