/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cont.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:44:49 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/15 21:43:56 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function to check if the command can work as the path for execve and if not
to print an error message */
char	*ft_path_is_cmd(t_token *tok, t_cnst *consts, int index)
{
	int	error;

	error = ft_strcpy_ms(tok[index].cmd[0], &tok[index].path);
	if (error == -1)
		ft_cleanup(tok, consts, errno);
	if (!ft_strchr(tok[index].cmd[0], '/') || access(tok[index].cmd[0],
			F_OK | X_OK) == -1)
	{
		if (errno == 0)
			(errno = ENOENT);
		if (errno == ENOENT)
			ft_cmd_not_fnd(tok, consts, index);
		else if (errno == EACCES)
		{
			perror(tok[index].cmd[0]);
			consts->exit_code = 126;
		}
		else
		{
			perror(tok[index].cmd[0]);
			consts->exit_code = 1;
		}
		free(tok[index].path);
		return (NULL);
	}
	return (tok[index].path);
}

/* function to print command not found to standard error */
void	ft_cmd_not_fnd(t_token *tok, t_cnst *consts, int index)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, tok[index].cmd[0], ft_strlen(tok[index].cmd[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "command not found\n", 18);
	consts->exit_code = 127;
}
