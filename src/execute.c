/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:05:13 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/10 18:02:29 by gstronge         ###   ########.fr       */
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
void	ft_execute_child(t_token *tok, t_cnst *consts, int index, int pipefd[2])
{
	tok->cmd = ft_expand_dollar(tok, consts, &tok[index]);
	tok->cmd = ft_remove_quotes(tok[index].cmd);
	// printf("A REMOVE QUOTES tok[index].cmd[0] =>%s<, cmd[1]=>%s<, cmd[2]=>%s<\n\n", tok[index].cmd[0], tok[index].cmd[1], tok[index].cmd[2]);
	if (index > 0)
	{
		dup2(tok[index].input_fd, 0);
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
	int	pipefd[2];
	int	index;
	int	saved_stdin;
	int	saved_stdout;

	index = 0;
	while (index < consts->tok_num)
	{
		if (index < consts->tok_num - 1)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
		}
		if (ft_is_builtin(tok[index].cmd[0]))
		{
			saved_stdin = dup(STDIN_FILENO);
			saved_stdout = dup(STDOUT_FILENO);
			ft_redirect(&tok[index]);
			ft_execute_builtins(tok, consts, index);
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return ;
		}
		else
		{
			tok[index].pid = fork();
			if (tok[index].pid == 0)
			{
				ft_execute_child(tok, consts, index, pipefd);
				exit(EXIT_SUCCESS);
			}
			else
				ft_execute_parent(tok, index, pipefd, consts);
		}
		tok[index].input_fd = pipefd[1];
		index++;
	}
	ft_wait(tok, consts);
}
