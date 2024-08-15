/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:15:31 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/15 20:09:06 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_fill_tok(t_token *tok, t_cnst *consts, char *tok_str, int index)
{
	tok[index].cmd = ft_split_ms(tok_str, ' ');
	if (tok[index].cmd == NULL)
	{
		free(tok_str);
		ft_cleanup(tok, consts, errno);
	}
	if (tok[index].cmd[0] == NULL)
	{
		free(tok[index].cmd);
		tok[index].cmd = NULL;
	}
	ft_redir_file(tok, consts, tok_str, index);
	return (tok);
}

void	ft_redir_file(t_token *tok, t_cnst *consts, char *tok_str, int index)
{
	char	quote_symb;
	int		i;
	int		i_change;

	i = 0;
	i_change = 0;
	while (tok_str[i] != '\0')
	{
		if (tok_str[i] == '\'' || tok_str[i] == '"')
		{
			quote_symb = tok_str[i];
			i++;
			while (tok_str[i] != quote_symb)
				i++;
		}
		i_change = ft_fill_redirs(tok, &tok_str[i], index);
		if (i_change == -1)
		{
			free(tok_str);
			ft_cleanup(tok, consts, errno);
		}
		i = i + i_change;
		i++;
	}
}

int	ft_handle_output_redirs(t_token *tok, char *tok_str, int index)
{
	int	i;

	i = 0;
	if (tok_str[i] == '>' && tok_str[i + 1] == '>')
	{
		tok[index].out_a = ft_cpy_redir(tok[index].out_a, &tok_str[i + 2]);
		if (tok[index].out_a == NULL)
			return (-1);
		i++;
	}
	else if (tok_str[i] == '>')
	{
		tok[index].out = ft_cpy_redir(tok[index].out, &tok_str[i + 1]);
		if (tok[index].out == NULL)
			return (-1);
	}
	return (i);
}

int	ft_handle_input_redirs(t_token *tok, char *tok_str, int index)
{
	int	i;

	i = 0;
	if (tok_str[i] == '<' && tok_str[i + 1] == '<')
	{
		tok[index].heredoc = ft_cpy_redir(tok[index].heredoc, &tok_str[i + 2]);
		if (tok[index].heredoc == NULL)
			return (-1);
		i++;
	}
	else if (tok_str[i] == '<')
	{
		tok[index].in = ft_cpy_redir(tok[index].in, &tok_str[i + 1]);
		if (tok[index].in == NULL)
			return (-1);
	}
	return (i);
}

int	ft_fill_redirs(t_token *tok, char *tok_str, int index)
{
	int	i;

	i = 0;
	if (tok_str[i] == '>' || tok_str[i] == '<')
	{
		if (tok_str[i] == '>')
			i = ft_handle_output_redirs(tok, tok_str, index);
		else if (tok_str[i] == '<')
			i = ft_handle_input_redirs(tok, tok_str, index);
		if (i == -1)
			return (-1);
	}
	return (i);
}
