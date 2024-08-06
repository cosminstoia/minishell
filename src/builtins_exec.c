/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:45:48 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/06 18:27:56 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Functions that execute the builtin commands
void	ft_execute_builtins(t_token *tok, t_cnst *consts, int index,
		int output_fd)
{
	tok->cmd = ft_expand_dollar(tok, consts, &tok[index]);
	tok->cmd = ft_remove_quotes(tok[index].cmd);
	if (ft_strncmp(tok[index].cmd[0], "echo", 5) == 0)
		ft_execute_echo(&tok[index], output_fd);
	else if (ft_strncmp(tok[index].cmd[0], "cd", 3) == 0)
		ft_execute_cd(&tok[index], consts);
	else if (ft_strncmp(tok[index].cmd[0], "pwd", 4) == 0)
		ft_execute_pwd(consts, output_fd);
	else if (ft_strncmp(tok[index].cmd[0], "env", 4) == 0)
		ft_execute_env(consts, output_fd);
	else if (ft_strncmp(tok[index].cmd[0], "unset", 6) == 0)
		ft_execute_unset(&tok[index], consts);
	else if (ft_strncmp(tok[index].cmd[0], "export", 7) == 0)
		ft_execute_export(&tok[index], consts);
	else if (ft_strncmp(tok->cmd[0], "exit", 5) == 0)
		ft_execute_exit(tok, consts, &tok[index]);
}

// Function that checks if a command is a builtin or not
int	ft_is_builtin(char *cmd)
{
	return (ft_strncmp(cmd, "echo", 5) == 0 || ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0 || ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0 || ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0);
}
