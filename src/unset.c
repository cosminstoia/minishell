/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:29:33 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/11 18:27:54 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to remove an environment variable
static void	remove_env_var(char *var, char **environ)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	len = ft_strlen(var);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			j = i;
			while (environ[j])
			{
				environ[j] = environ[j + 1];
				j++;
			}
			break ;
		}
		else
			i++;
	}
}

// Function to handle special cases such as PATH
static void	handle_special_cases(char *var, t_cnst *consts)
{
	if (ft_strncmp(var, "PATH=", 5) == 0)
	{
		ft_free_splits(consts->env_p);
		consts->env_p = NULL;
	}
}

// Refactored main function to use the helper functions
void	ft_execute_unset(t_token *tok, t_cnst *consts)
{
	char	*var;

	if (!tok->cmd[1])
		return ;
	var = tok->cmd[1];
	remove_env_var(var, consts->environ);
	handle_special_cases(var, consts);
	consts->exit_code = 0;
}
