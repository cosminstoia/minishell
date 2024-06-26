/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:15:31 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/26 19:24:48 by gstronge         ###   ########.fr       */
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
	tok[index].path = ft_make_path(tok, consts, tok_str, index);
	ft_redir_file(tok, consts, tok_str, index);
	return (tok);
}

void	ft_redir_file(t_token *tok, t_cnst *consts, char *tok_str, int index)
{
	int	i;

	i = 0;
	while (tok_str[i] != '\0')
	{
		if (tok_str[i] == '>' && tok_str[i + 1] == '>')
		{
			tok[index].out_a = ft_cpy_redir(tok, consts, &tok[index].out_a[0], &tok_str[i + 2]);
			i++;
		}
		else if (tok_str[i] == '>')
			tok[index].out = ft_cpy_redir(tok, consts, &tok[index].out[0], &tok_str[i + 1]);
		else if (tok_str[i] == '<' && tok_str[i + 1] == '<')
		{
			tok[index].heredoc = ft_cpy_redir(tok, consts, &tok[index].heredoc[0], &tok_str[i + 2]);
			i++;
		}
		else if (tok_str[i] == '<')
			tok[index].in = ft_cpy_redir(tok, consts, &tok[index].in[0], &tok_str[i + 1]);
		i++;
	}
}

char	*ft_cpy_redir(t_token *tok, t_cnst *consts, char *tok_str, char *str)
{
	int	strlen;
	int	i;

	strlen = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i + strlen] != '\0' && str[i + strlen] != ' ')
		strlen++;
	tok_str = (char *)malloc((strlen + 1) * sizeof(char));
	if (tok_str == NULL)
	{
		free(tok_str);
		ft_cleanup(tok, consts, errno);
	}
	strlen = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		tok_str[strlen] = str[i];
		i++;
		strlen++;
	}
	tok_str[strlen] = '\0';
	return (tok_str);
}
