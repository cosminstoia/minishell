/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:02:08 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/30 14:21:02 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to check if there is provided an argument
static void	print_declaration(char *env)
{
	int		i;
	char	*equal_sign;

	equal_sign = ft_strchr(env, '=');
	if (equal_sign)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		i = 0;
		while (env[i] != '=')
			write(STDOUT_FILENO, &env[i++], 1);
		write(STDOUT_FILENO, "=\"", 2);
		while (env[++i] != '\0')
			write(STDOUT_FILENO, &env[i], 1);
		write(STDOUT_FILENO, "\"\n", 2);
	}
	else
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

int	ft_check_argument(t_token *tok, t_cnst *consts)
{
	int	index;

	if (tok->cmd[1] == NULL)
	{
		index = 0;
		while (consts->environ[index] != NULL)
			print_declaration(consts->environ[index++]);
		return (0);
	}
	return (1);
}

// Function to check if the variable already exists
int	ft_check_var(t_token *tok, t_cnst *consts)
{
	int	i;

	i = 0;
	while (consts->environ[i])
	{
		if (ft_strncmp(consts->environ[i], tok->cmd[1],
				ft_strlen(tok->cmd[1])) == 0
			&& consts->environ[i][ft_strlen(tok->cmd[1])] == '=')
		{
			free(consts->environ[i]);
			break ;
		}
		i++;
	}
	return (i);
}

// Update or add the new variable to the environment array
void	ft_add_var(t_cnst *consts, char *new_var, int i)
{
	if (consts->environ[i] == NULL)
	{
		consts->environ[i] = new_var;
		consts->environ[i + 1] = NULL;
	}
	else
		consts->environ[i] = new_var;
}

// Function to realloc the environment variable 2D array so an extra environment
// variable can be added.
char	**ft_realloc_env(t_token *tok, t_cnst *consts)
{
	char	**new_env;
	int		index;

	index = 0;
	while (consts->environ[index])
		index++;
	new_env = (char **)malloc((index + 2) * sizeof(char *));
	if (new_env == NULL)
		ft_cleanup(tok, consts, errno);
	index = 0;
	while (consts->environ[index])
	{
		new_env[index] = consts->environ[index];
		index++;
	}
	new_env[index] = NULL;
	index++;
	new_env[index] = NULL;
	free(consts->environ);
	return (new_env);
}
