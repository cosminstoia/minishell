/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/25 20:32:38 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_execute_nonbuiltins(t_token *tok, char *input)
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

void	ft_execute(t_token *tok, char *input)
{
	(void)input;
	ft_handle_sig();
	if (ft_strncmp(tok->cmd[0], "echo", 5) == 0)
		ft_execute_echo(tok);
	else if (ft_strncmp(tok->cmd[0], "cd", 3) == 0)
		ft_execute_cd(tok);
	else
		ft_execute_nonbuiltins(tok, input);
}