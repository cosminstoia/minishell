/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/25 19:15:33 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exec_cmds(t_token *tok, char *input)
{
	extern char	**environ;
	int			*status;

	status = NULL;
	tok->pid = fork();
	if (tok->pid == -1)
		ft_cleanup(tok, input, errno);
	if (tok->pid == 0)
		execve(tok->path, tok->cmd, environ);
	waitpid(tok->pid, status, 0);
}
