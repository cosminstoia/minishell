/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:16:37 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/07 15:22:20 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (input[i] == '\0' || input[i] == '|' || input[i] == '<'
		|| input[i] == '>')
		err_char = input[i];
	return (err_char);
}

/* function to find the error character if there are redirects */
char	ft_redir_err_char(char *input, char err_char, int i)
{
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
		else if (input[i + 1] == '>' && (input[i + 2] == '<' \
				|| input[i + 2] == '>'))
			err_char = input[i + 2];
		else
			err_char = ft_no_redir_name(input, err_char, i);
	}
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
		err_char = ft_redir_err_char(input, err_char, i);
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
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '|')
			return ('|');
		while (input[i] != '\0' && input[i] != '|')
			i++;
		if (input[i] == '|')
			i++;
	}
	return (err_char);
}
