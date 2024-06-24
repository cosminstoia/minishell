/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:22:15 by cstoia            #+#    #+#             */
/*   Updated: 2024/06/24 11:13:53 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to execute the "echo" and "echo -n" command
void	ft_execute_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

// Function to execute the "cd" command in the parent process
void	ft_execute_cd(char *directory)
{
	if (chdir(directory) != 0)
		printf("Error; chdir failed");
}

// Function to execute the "export" command
void	ft_execute_export(char **args)
{
	extern char	**environ;
	char		*var_value;
	char		*equal_sign;
	char		*var_name;
	char		*value;
	int			i;

	i = 0;
	if (args[1] == NULL)
	{
		while (environ[i] != NULL)
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return ;
	}
	var_value = args[1];
	equal_sign = ft_strchr(var_value, '=');
	if (equal_sign == NULL)
	{
		printf("export: invalid format. Use export VAR=value\n");
		return ;
	}
	*equal_sign = '\0';
	var_name = var_value;
	value = equal_sign + 1;
	if (setenv(var_name, value, 1) != 0)
		printf("export: failed to set %s\n");
}

// int	main(int argc, char *argv[])
// {
// 	if (argc < 2)
// 	{
// 		fprintf(stderr, "Usage: %s <command> [arguments]\n", argv[0]);
// 		return (1);
// 	}
// 	if (strcmp(argv[1], "cd") == 0)
// 	{
// 		if (argc < 3)
// 		{
// 			fprintf(stderr, "cd: missing argument\n");
// 			return (1);
// 		}
// 		ft_execute_cd(argv[2]);
// 	}
// 	else if (strcmp(argv[1], "echo") == 0)
// 		ft_execute_echo(argv);
// 	else if (strcmp(argv[1], "export") == 0)
// 		ft_execute_export(argv);
// 	else
// 	{
// 		fprintf(stderr, "Unknown command: %s\n", argv[1]);
// 		return (1);
// 	}
// 	return (0);
// }