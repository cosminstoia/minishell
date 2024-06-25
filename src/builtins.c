/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:22:15 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/25 22:06:34 by cstoia           ###   ########.fr       */
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
void	ft_execute_cd(t_token *tok)
{
	char	*target_directory;
	char	*current_directory;

	target_directory = NULL;
	if (tok->cmd[1] != NULL && strncmp(tok->cmd[1], "-", 2) == 0)
	{
		target_directory = getenv("OLDPWD");
		if (target_directory == NULL)
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		printf("%s\n", target_directory);
	}
	else if (tok->cmd[1] == NULL || strncmp(tok->cmd[1], "~", 2) == 0)
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

// // Function to execute the "export" command
// void	ft_execute_export(char **args)
// {
// 	extern char	**environ;
// 	char		*var_value;
// 	char		*equal_sign;
// 	char		*var_name;
// 	char		*value;
// 	int			i;

// 	i = 0;
// 	if (args[1] == NULL)
// 	{
// 		while (environ[i] != NULL)
// 		{
// 			printf("%s\n", environ[i]);
// 			i++;
// 		}
// 		return ;
// 	}
// 	var_value = args[1];
// 	equal_sign = ft_strchr(var_value, '=');
// 	if (equal_sign == NULL)
// 	{
// 		printf("export: invalid format. Use export VAR=value\n");
// 		return ;
// 	}
// 	*equal_sign = '\0';
// 	var_name = var_value;
// 	value = equal_sign + 1;
// 	if (setenv(var_name, value, 1) != 0)
// 		printf("export: failed to set %s\n");
// }