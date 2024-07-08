/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:27:39 by gstronge          #+#    #+#             */
/*   Updated: 2024/07/01 14:04:54 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// function to parse the input and create an array of token structs. Each token
// contains the information required to execute a single command
t_token	*ft_parse_input(t_token *tok, t_cnst *consts)
{
	char	*tok_str;

	tok_str = NULL;
	consts->tok_num = 0;
	consts->tok_num = ft_token_num(consts->input, consts->tok_num);
	tok = (t_token *)malloc((consts->tok_num) * sizeof(t_token));
	if (tok == NULL)
		ft_cleanup(tok, consts, errno);
	tok = ft_make_toks(tok, consts, tok_str, consts->tok_num);
	return (tok);
}

// function that uses the input string to find the number of tokens required
int	ft_token_num(char *input, int tok_num)
{
	int i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] != '\0')
		tok_num++;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\0' && input[i] != '\'')
				i++;
		}
		else if (input[i] == '"')
		{
			i++;
			while (input[i] != '\0' && input[i] != '"')
				i++;
		}
		else if (input[i] == '|' && input[i + 1] != '|')
			tok_num++;
		i++;
	}
	return (tok_num);
}

// function to initialise the structs' variables
t_token	*ft_init_tok(t_token *tok, int index)
{
	tok[index].cmd = NULL;
	tok[index].path = NULL;
	tok[index].in = NULL;
	tok[index].out = NULL;
	tok[index].out_a = NULL;
	tok[index].heredoc = NULL;
	tok[index].input_fd = 0;
	return (tok);
}

// function to copy the string from input until the next pipe
int	ft_cpy_tok_str(char *input, char *tok_str, int i)
{
	int	j;

	j = 0;
	while (input[i] != '\0' && input[i] != '|')
	{
		tok_str[j] = input[i];
		i++;
		j++;
	}
	tok_str[j] = '\0';
	if (input[i] == '|')
		i++;
	return (i);
}

// function to make all structs of tokens in the tok_array
t_token	*ft_make_toks(t_token *tok, t_cnst *consts, char *tok_str, int tok_num)
{
	int	index;
	int	len;
	int	i;

	index = 0;
	i = 0;
	while (index < tok_num)
	{
		len = 0;
		if (tok_str != NULL)
			free(tok_str);
		while (consts->input[len + i] != '\0' && consts->input[len + i] != '|')
			len++;
		tok_str = (char *)malloc((len + 1) * sizeof(char));
		if (tok_str == NULL)
			ft_cleanup(tok, consts, errno);
		i = ft_cpy_tok_str(consts->input, tok_str, i);
		tok = ft_init_tok(tok, index);
		tok = ft_fill_tok(tok, consts, tok_str, index);
		index++;
	}
	free(tok_str);
	return (tok);
}
