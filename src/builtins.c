/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:22:15 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/12 17:46:51 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to execute the "echo" and "echo -n" command
void	ft_execute_echo(t_token *tok, t_cnst *consts, int output_fd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (tok->cmd[i] && ft_strncmp(tok->cmd[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	if (tok->cmd[i] && ft_strncmp(tok->cmd[i], "~", 2) == 0)
	{
		ft_putstr_fd(getenv("HOME"), output_fd);
		i++;
	}
	while (tok->cmd[i])
	{
		ft_putstr_fd(tok->cmd[i], output_fd);
		if (tok->cmd[i + 1])
			write(output_fd, " ", 1);
		i++;
	}
	if (newline)
		write(output_fd, "\n", 1);
	consts->exit_code = 0;
}

// Function to execute the "pwd" command
void	ft_execute_pwd(t_cnst *consts, int output_fd)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, output_fd);
		write(output_fd, "\n", 1);
	}
	else
	{
		perror("pwd");
		consts->exit_code = 1;
	}
	consts->exit_code = 0;
}

// Function to execute the "env" command
void	ft_execute_env(t_cnst *consts, int output_fd)
{
	char	**env;
	char	*underscore_var;

	underscore_var = "_=";
	env = consts->environ;
	while (*env)
	{
		if (ft_strncmp(*env, underscore_var, 2) == 0)
			ft_putstr_fd("_=/usr/bin/env", output_fd);
		else if (ft_strchr(*env, '='))
			ft_putstr_fd(*env, output_fd);
		if (ft_strchr(*env, '='))
			write(output_fd, "\n", 1);
		env++;
	}
}

/* function that tries to find a string in the environment variable list and if
it finds a match, returns a pointer to the variable */
char	*ft_return_env_var(t_cnst *consts, char *find_str)
{
	int	strlen;
	int	i;

	i = 0;
	strlen = ft_strlen(find_str);
	while (consts->environ[i])
	{
		if (!ft_strncmp(find_str, consts->environ[i], strlen))
			return (&consts->environ[i][strlen]);
		i++;
	}
	return (NULL);
}
