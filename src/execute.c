/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/28 20:18:40 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_execute_nonbuiltins(t_token *tok, t_cnst *consts, int index)
{
	tok[index].path = ft_make_path(tok, consts, index);
	tok[index].pid = fork();
	if (tok[index].pid == -1)
		ft_cleanup(tok, consts, errno);
	if (tok[index].pid == 0)
	{
		ft_redirect(&tok[index]);
		execve(tok[index].path, tok[index].cmd, consts->environ);
		exit(0);
	}
}

void	ft_execute(t_token *tok, t_cnst *consts)
{
	int	index;

	index = 0;
	while (index < consts->tok_num)
	{
		if (ft_strncmp(tok[index].cmd[0], "echo", 5) == 0)
			ft_execute_echo(tok);
		else if (ft_strncmp(tok[index].cmd[0], "cd", 3) == 0)
			ft_execute_cd(tok, consts);
		else if (ft_strncmp(tok[index].cmd[0], "pwd", 4) == 0)
			ft_execute_pwd();
		else if (ft_strncmp(tok[index].cmd[0], "env", 4) == 0)
			ft_execute_env(consts);
		else if (ft_strncmp(tok[index].cmd[0], "unset", 6) == 0)
			ft_execute_unset(tok, consts);
		else if (ft_strncmp(tok[index].cmd[0], "export", 7) == 0)
			ft_execute_export(tok, consts);
		else
			ft_execute_nonbuiltins(tok, consts, index);
		index++;
	}
	ft_wait(tok, consts);
}

void	ft_wait(t_token *tok, t_cnst *consts)
{
	int	status;
	int	index;

	index = 0;
	while (index < consts->tok_num)
	{
		waitpid(tok[index].pid, &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			perror("waitpid error");
		index++;
	}
}