/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:24:49 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/16 14:03:16 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to find a variable in the environment
static int	find_env_index(char **env, const char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	**ft_new_environ(t_cnst *consts, char **new_environ,
		char *new_shlvl_env)
{
	int	i;

	i = 0;
	while (consts->environ[i])
		i++;
	new_environ = (char **)malloc(sizeof(char *) * (i + 2));
	if (!consts->environ)
	{
		free(new_shlvl_env);
		ft_cleanup(NULL, consts, errno);
	}
	i = 0;
	while (consts->environ[i])
	{
		new_environ[i] = consts->environ[i];
		i++;
	}
	new_environ[i] = new_shlvl_env;
	new_environ[i + 1] = NULL;
	return (new_environ);
}

static char	**ft_update_env(t_cnst *consts, int shlvl_index,
		char *new_shlvl_env)
{
	char	**new_environ;

	new_environ = NULL;
	if (shlvl_index != -1)
	{
		free(consts->environ[shlvl_index]);
		consts->environ[shlvl_index] = new_shlvl_env;
	}
	else
	{
		new_environ = ft_new_environ(consts, new_environ, new_shlvl_env);
		return (new_environ);
	}
	return (consts->environ);
}

void	update_shlvl(t_cnst *consts)
{
	int		shlvl_index;
	int		shlvl;
	char	*new_shlvl_env;
	char	*new_shlvl_str;
	int		total_len;

	shlvl_index = find_env_index(consts->environ, "SHLVL");
	shlvl = 1;
	if (shlvl_index != -1)
		shlvl = 1 + ft_atoi(consts->environ[shlvl_index] + 6);
	new_shlvl_str = ft_itoa(shlvl);
	total_len = ft_strlen("SHLVL=") + ft_strlen(new_shlvl_str) + 1;
	new_shlvl_env = (char *)malloc(total_len * sizeof(char));
	if (!new_shlvl_env)
	{
		perror("malloc failed");
		ft_cleanup(NULL, consts, errno);
	}
	ft_strlcpy(new_shlvl_env, "SHLVL=", total_len);
	ft_strlcat(new_shlvl_env, new_shlvl_str, total_len);
	consts->environ = ft_update_env(consts, shlvl_index, new_shlvl_env);
	free(new_shlvl_str);
}
