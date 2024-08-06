/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:44:55 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/06 14:32:04 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_set_exit(char *error, t_token *tok, t_cnst *consts,
		int exit_code)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, tok->cmd[0], ft_strlen(tok->cmd[0]));
	write(STDERR_FILENO, ": ", 2);
	ft_putstr_fd(error, STDERR_FILENO);
	consts->exit_code = exit_code;
}
