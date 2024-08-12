/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:20:57 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/12 15:23:35 by cstoia           ###   ########.fr       */
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
		if (!consts->input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (consts->input)
			ft_use_input(tok, consts);
		free(consts->input);
	}
}

/* function to make the consts struct, a structure that stores variables that
 remain constant no matter which comand is being executed */
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
	consts->exit_code = 0;
	return (consts);
}

/* function to make the environment path variable that is required by the execve
 function during execution */
char	**ft_make_env_path(t_token *tok, t_cnst *consts)
{
	char	*env_path_str;

	env_path_str = ft_return_env_var(consts, "PATH=");
	consts->env_p = ft_split_ms(env_path_str, ':');
	if (consts->env_p == NULL)
		ft_cleanup(tok, consts, errno);
	return (consts->env_p);
}

/* function to check if there are any errors in the user input */
int	ft_input_error(t_cnst *consts, char *input)
{
	char	err_char;

	err_char = 'x';
	if (!ft_quotes_close(input))
	{
		printf("minishell: Error: quotes must be closed\n");
		consts->exit_code = 258;
		return (1);
	}
	err_char = ft_redir_error(input, err_char);
	if (err_char == 'x')
		err_char = ft_only_pipe(input, err_char);
	if (err_char != 'x')
	{
		printf("minishell: syntax error near unexpected token '%c'\n",
			err_char);
		consts->exit_code = 258;
		return (1);
	}
	return (0);
}

void	ft_use_input(t_token *tok, t_cnst *consts)
{
	add_history(consts->input);
	if (!ft_input_error(consts, consts->input))
	{
		tok = ft_parse_input(tok, consts);
		ft_execute(tok, consts);
		if (consts->tok_num == 0)
			consts->exit_code = 0;
		ft_free_tok(tok, consts);
	}
}
