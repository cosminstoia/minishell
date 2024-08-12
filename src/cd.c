/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:46:08 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/12 22:23:36 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_update_oldpwd(t_cnst *consts)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		consts->exit_code = 1;
		return ;
	}
	while (consts->environ[i])
	{
		if (ft_strncmp(consts->environ[i], "OLDPWD", 6) == 0)
		{
			free(consts->environ[i]);
			consts->environ[i] = ft_strjoin("OLDPWD=", cwd);
		}
		i++;
	}
}

static void	ft_update_pwd(t_cnst *consts)
{
	char	cwd[PATH_MAX];
	int		i;

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		consts->exit_code = 1;
		return ;
	}
	while (consts->environ[i])
	{
		if (ft_strncmp(consts->environ[i], "PWD", 3) == 0)
		{
			free(consts->environ[i]);
			consts->environ[i] = ft_strjoin("PWD=", cwd);
		}
		i++;
	}
}

static void	ft_update_var(t_cnst *consts, char *target_directory)
{
	ft_update_oldpwd(consts);
	if (chdir(target_directory) != 0)
	{
		perror("cd");
		consts->exit_code = 1;
	}
	ft_update_pwd(consts);
}

// Function to execute the "cd" command in the parent process
void	ft_execute_cd(t_token *tok, t_cnst *consts)
{
	char	*target_directory;

	target_directory = NULL;
	if (tok->cmd[1] != NULL && ft_strncmp(tok->cmd[1], "-", 2) == 0)
	{
		target_directory = ft_return_env_var(consts, "OLDPWD=");
		if (target_directory == NULL)
			return (ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO));
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
	ft_update_var(consts, target_directory);
	consts->exit_code = 0;
}
