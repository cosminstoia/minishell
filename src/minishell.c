/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:20:57 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/27 16:13:45 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cnst	*consts;
	t_token	*tok;

	consts = NULL;
	tok = NULL;
	if (argc != 1 || argv == NULL)
		exit(EXIT_FAILURE);
	consts = ft_make_consts(consts, env);
	ft_handle_sig();
	while (1)
	{
		consts->input = readline("minishell: ");
		if (consts->input == NULL)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		// if (consts->input == NULL)
		// 	ft_input_null();
		if (consts->input)
		{
			add_history(consts->input);
			// ft_input_error(input);
			// if (!ft_strncmp("minishell", consts->input, 10))
			// 	ft_new_shell();
			tok = ft_parse_input(tok, consts);
			ft_execute(tok, consts);
			ft_free_tok(tok, consts);
		}
		if (consts->input != NULL)
			free(consts->input);
	}
}

char	*ft_return_env_var(t_cnst *consts, char *find_str)
{
	int	strlen;
	int	i;

	i = 0;
	strlen = ft_strlen(find_str);
	while (consts->environ[i])
	{
		if (!ft_strncmp(find_str, consts->environ[i], strlen))
			return (&consts->environ[i][strlen + 1]);
		i++;
	}
	return (NULL);
}

char	**ft_make_env_path(t_token *tok, t_cnst *consts)
{
	char	*env_path_str;

	if (consts->env_p != NULL)
		free(consts->env_p);
	env_path_str = ft_return_env_var(consts, "PATH");
	consts->env_p = ft_split_ms(env_path_str, ':');
	if (consts->env_p == NULL)
		ft_cleanup(tok, consts, errno);
	return (consts->env_p);
}

t_cnst	*ft_make_consts(t_cnst *consts, char **env)
{
	int	env_vars;
	int	i;

	env_vars = 0;
	i = 0;
	while (env[env_vars] != NULL)
		env_vars++;
	consts = (t_cnst *)malloc(sizeof(t_cnst));
	if (consts == NULL)
		exit(errno);
	consts->environ = (char **)malloc((env_vars + 1) * sizeof(char *));
	if (consts->environ == NULL)
		ft_cleanup(NULL, consts, errno);
	while (i < env_vars)
	{
		consts->environ[i] = ft_strdup(env[i]);
		if (consts->environ[i] == NULL)
			ft_cleanup(NULL, consts, errno);
		i++;
	}
	consts->environ[i] = NULL;
	consts->env_p = ft_make_env_path(NULL, consts);
	consts->input = NULL;
	consts->tok_num = 0;
	return (consts);
}
