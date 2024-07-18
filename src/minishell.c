/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:20:57 by gstronge          #+#    #+#             */
/*   Updated: 2024/07/18 19:09:04 by cstoia           ###   ########.fr       */
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
		//printf("%s\n", consts->input);
		if (!consts->input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (consts->input)
		{
			add_history(consts->input);
			if (!ft_input_error(consts, consts->input))
			{
				// if (!ft_strncmp("minishell", consts->input, 10))
				// 	ft_new_shell();
				tok = ft_parse_input(tok, consts);
				ft_execute(tok, consts);
				ft_free_tok(tok, consts);
			}
		}
		free(consts->input);
	}
}

/* function to check if there are any in the commands entered by the user */
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
		printf("minishell: syntax error near unexpected token '%c'\n", err_char);
		consts->exit_code = 258;
		return (1);
	}
	return (0);
}

/* function to check if any quotes that are opened, also close */
int	ft_quotes_close(char *input)
{
	char	quote_symb;
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote_symb = input[i];
			i++;
			while (input[i] != '\0')
			{
				if (input[i] == quote_symb)
					break ;
				i++;
			}
			if (input[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}

/* function to check if a filename is given after the redirection symbol */
char	ft_no_redir_name(char *input, char err_char, int i)
{
	while (input[i] == '>' || input[i] == '<')
		i++;
	if (input[i] == '\0')
		return (input[i - 1]);
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '\0' || input[i] == '|' || input[i] == '<' || input[i] == '>')
		err_char = input[i];
	return (err_char);
}

/* function to check if there are any syntax errors in the redirects */
char	ft_redir_error(char *input, char err_char)
{
	char	quote_symb;
	int		i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote_symb = input[i];
			i++;
			while (input[i] != quote_symb)
				i++;
		}
		if (input[i] == '<')
		{
			if (input[i + 1] == '<' && (input[i + 2] == '<' || input[i + 2] == '>'))
				err_char = input[i + 2];
			else
				err_char = ft_no_redir_name(input, err_char, i);
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '<')
				err_char = '<';
			else if (input[i + 1] == '>' && (input[i + 2] == '<' || input[i + 2] == '>'))
				err_char = input[i + 2];
			else
				err_char = ft_no_redir_name(input, err_char, i);
		}
		if (err_char != 'x')
			break ;
		if (input[i] != '>' && input[i] != '<')
			i++;
		else
		{
			while (input[i] == '>' || input[i] == '<')
				i++;
		}
	}
	return (err_char);
}

/* function to check if there is no command before or after a pipe symbol */
char	ft_only_pipe(char *input, char err_char)
{
	int last_pipe;
	int	i;

	last_pipe = 0;
	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '|')
		err_char = '|';
	else
	{
		while (input[i] != '\0')
		{
			if (input[i] == '|')
				last_pipe = i;
			i++;
		}
		if (input[last_pipe] != '\0')
			i = last_pipe + 1;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0' && last_pipe > 0)
			err_char = '|';
		else if (last_pipe > 0 && (input[i] == '>' || input[i] == '<'))
			err_char = input[i];
	}
	return (err_char);
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

/* function to make the environment path variable that is required by the execve
 function during execution */
char	**ft_make_env_path(t_token *tok, t_cnst *consts)
{
	char	*env_path_str;

	// if (consts->env_p != NULL)
	// 	free(consts->env_p);
	env_path_str = ft_return_env_var(consts, "PATH=");
	consts->env_p = ft_split_ms(env_path_str, ':');
	if (consts->env_p == NULL)
		ft_cleanup(tok, consts, errno);
	return (consts->env_p);
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
	consts->tok_num = 0;
	consts->exit_code = 0;//can this be moved to another fucntion? since it should set to 0 default
	return (consts);
}
