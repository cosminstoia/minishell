/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/27 13:59:42 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_execute_nonbuiltins(t_token *tok, t_cnst *consts)
{
	int	*status;

	status = NULL;
	tok->pid = fork();
	if (tok->pid == -1)
		ft_cleanup(tok, consts, errno);
	tok->path = ft_make_path(tok, consts, NULL, index);
	if (tok->pid == 0)
		execve(tok->path, tok->cmd, consts->environ);
	waitpid(tok->pid, status, 0);
}

void	ft_execute(t_token *tok, t_cnst *consts)
{
	if (ft_strncmp(tok->cmd[0], "echo", 5) == 0)
		ft_execute_echo(tok);
	else if (ft_strncmp(tok->cmd[0], "cd", 3) == 0)
		ft_execute_cd(tok, consts);
	else if (ft_strncmp(tok->cmd[0], "pwd", 4) == 0)
		ft_execute_pwd();
	else if (ft_strncmp(tok->cmd[0], "env", 4) == 0)
		ft_execute_env(consts);
	else if (ft_strncmp(tok->cmd[0], "unset", 6) == 0)
		ft_execute_unset(tok, consts);
	else if (ft_strncmp(tok->cmd[0], "export", 7) == 0)
		ft_execute_export(tok, consts);
	else
		ft_execute_nonbuiltins(tok, consts);
}
