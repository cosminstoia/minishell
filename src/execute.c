/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/12 01:41:33 by cstoia           ###   ########.fr       */
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
		if (WIFEXITED(status))
			tok->exit_code = WEXITSTATUS(status);
		else
			tok->exit_code = 1;
		index++;
	}
}

/* Redirect input if not the first command
Redirect output if not the last command
Redirect any additional file descriptors as needed
Check if the command is a built-in function
Execute external command using execve */
void	ft_execute_child(t_token *tok, t_cnst *consts, int index, int pipefd[2])
{
	tok->cmd = ft_expand_dollar(tok, consts, &tok[index]);
	tok->cmd = ft_remove_quotes(tok[index].cmd);
	//(void)pipefd;
	// printf("A REMOVE QUOTES tok[index].cmd[0] =>%s<,
	// cmd[1]=>%s<,cmd[2]=>%s<\n\n", tok[index].cmd[0],
	// tok[index].cmd[1],tok[index].cmd[2]);
	if (index > 0)
	{
		dup2(tok[index].input_fd, STDIN_FILENO);
		close(tok[index].input_fd);
	}
	if (index < consts->tok_num - 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	ft_redirect(&tok[index]);
	tok[index].path = ft_make_path(tok, consts, index);
	execve(tok[index].path, tok[index].cmd, consts->environ);
}

/* Close input_fd if not the first command
Close pipefd[1] and update input_fd if not the last command */
void	ft_execute_parent(t_token *tok, int index, int pipefd[2],
		t_cnst *consts)
{
	if (index > 0)
		close(tok[index].input_fd);
	if (index < consts->tok_num - 1)
	{
		close(pipefd[1]);
		tok[index + 1].input_fd = pipefd[0];
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
	int pipefd[2];
	int index = 0;
	int output_fd;

	output_fd = -1;
	while (index < consts->tok_num)
	{
		if (index < consts->tok_num - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
			output_fd = pipefd[1];
		}
		else
			output_fd = STDOUT_FILENO;

		if (ft_is_builtin(tok[index].cmd[0]))
		{
			ft_redirect(&tok[index]);
			ft_execute_builtins(tok, consts, index, output_fd);
		}
		else
		{
			tok[index].pid = fork();
			if (tok[index].pid == 0)
				ft_execute_child(tok, consts, index, pipefd);
			else
				ft_execute_parent(tok, index, pipefd, consts);
		}

		if (index < consts->tok_num - 1)
			tok[index + 1].input_fd = pipefd[0];
		close(pipefd[1]);
		index++;
	}
	ft_wait(tok, consts);
}