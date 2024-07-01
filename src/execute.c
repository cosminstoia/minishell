/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/01 12:11:16 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function used to wait for the child process with pid tok[index].pid to complete
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

/* Redirect input if not the first command
Redirect output if not the last command
Redirect any additional file descriptors as needed
Check if the command is a built-in function
Execute external command using execve */
void	ft_execute_child(t_token *tok, t_cnst *consts, int index, int input_fd,
		int pipefd[2])
{
	if (index > 0)
	{
		dup2(input_fd, 0);
		close(input_fd);
	}
	if (index < consts->tok_num - 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	ft_redirect(&tok[index]);
	if (ft_is_builtin(tok[index].cmd[0]))
	{
		ft_execute_builtins(tok, consts, index);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(tok[index].path, tok[index].cmd, consts->environ);
		perror("execve error");
		exit(EXIT_FAILURE);
	}
}

/* Close input_fd if not the first command
Close pipefd[1] and update input_fd if not the last command */
void	ft_execute_parent(int index, int input_fd, int pipefd[2],
		t_cnst *consts)
{
	if (index > 0)
		close(input_fd);
	if (index < consts->tok_num - 1)
	{
		close(pipefd[1]);
		input_fd = pipefd[0];
	}
}

/* Loop through each command token
Create pipe if not the last command
Fork processes
Execute child function
Execute parent function
Wait for all child processes to complete */
void	ft_execute(t_token *tok, t_cnst *consts)
{
	int	index;
	int	pipefd[2];
	int	input_fd;

	input_fd = 0;
	index = 0;
	while (index < consts->tok_num)
	{
		tok[index].path = ft_make_path(tok, consts, index);
		if (index < consts->tok_num - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
		}
		tok[index].pid = fork();
		if (tok[index].pid == -1)
		{
			perror("fork error");
			ft_cleanup(tok, consts, errno);
			exit(EXIT_FAILURE);
		}
		if (tok[index].pid == 0)
			ft_execute_child(tok, consts, index, input_fd, pipefd);
		else
			ft_execute_parent(index, input_fd, pipefd, consts);
		index++;
	}
	ft_wait(tok, consts);
}
