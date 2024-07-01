/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:22:15 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/01 11:45:19 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to execute the "echo" and "echo -n" command
void	ft_execute_echo(t_token *tok)
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
	while (tok->cmd[i])
	{
		ft_putstr_fd(tok->cmd[i], STDOUT_FILENO);
		if (tok->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

// Function to execute the "cd" command in the parent process
void	ft_execute_cd(t_token *tok, t_cnst *consts)
{
	char	*target_directory;
	char	*current_directory;

	target_directory = NULL;
	if (tok->cmd[1] != NULL && ft_strncmp(tok->cmd[1], "-", 2) == 0)
	{
		target_directory = ft_return_env_var(consts, "OLDPWD");
		if (target_directory == NULL)
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		else
			printf("%s\n", target_directory);
	}
	else if (tok->cmd[1] == NULL || ft_strncmp(tok->cmd[1], "~", 2) == 0)
	{
		target_directory = getenv("HOME");
		if (target_directory == NULL)
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	}
	else
		target_directory = tok->cmd[1];
	current_directory = getcwd(NULL, 0);
	if (chdir(target_directory) != 0)
	{
		perror("chdir");
		return ;
	}
}

// Function to execute the "pwd" command
void	ft_execute_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		write(1, "\n", 1);
	}
	else
		perror("getcwd() error");
}

// Function to execute the "env" command
void	ft_execute_env(t_cnst *consts)
{
	char	**env;

	env = consts->environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

// Function to unset an environment variable
void	ft_execute_unset(t_token *tok, t_cnst *consts)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	if (!tok->cmd[1])
		return ;
	len = ft_strlen(tok->cmd[1]);
	while (consts->environ[i])
	{
		if (ft_strncmp(consts->environ[i], tok->cmd[1], len) == 0
			&& consts->environ[i][len] == '=')
		{
			free(consts->environ[i]);
			j = i;
			while (consts->environ[j])
			{
				consts->environ[j] = consts->environ[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	if (ft_strncmp(tok->cmd[1], "PATH", 5) == 0)
	{
		ft_free_splits(consts->env_p);
		consts->env_p = NULL;
	}
}
