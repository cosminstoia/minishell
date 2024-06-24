/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:15:31 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/24 16:10:55 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_fill_tok(t_token *tok, char *input, char *tok_str, int index)
{
	tok[index].env_p = ft_split_ms(getenv("PATH"), ':');
	if (tok[index].env_p == NULL)
	{
		free(tok_str);
		ft_cleanup(tok, input, errno);
	}
	tok[index].cmd = ft_split_ms(tok_str, ' ');
	if (tok[index].cmd == NULL)
	{
		free(tok_str);
		ft_cleanup(tok, input, errno);
	}
	// tok[index].path = ft_create_path(tok, input, index);
	// if (tok[index].path == NULL)
	// {
	// 	free(tok_str);
	// 	ft_cleanup(tok, input, errno);
	// }
	// ft_redir_file(tok, input, tok_str, index);
	return (tok);
}
