/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:41:33 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/24 10:59:04 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// two-dimensional char arrays are freed
void	ft_free_splits(char **strstr)
{
	int	i;

	i = 0;
	if (strstr)
	{
		while (strstr[i])
		{
			free(strstr[i]);
			i++;
		}
		free(strstr);
	}
}

// individual parts of the struct are freed
void	ft_free_tok(t_token *tok)
{
	if (tok->env_p)
		ft_free_splits(tok->env_p);
	if (tok->cmd)
		ft_free_splits(tok->cmd);
	if (tok->path)
		free(tok->path);
	if (tok->in)
		free(tok->in);
	if (tok->out)
		free(tok->out);
	if (tok->out)
		free(tok->out_a);
	if (tok->out)
		free(tok->heredoc);
	free(tok);
}

// all allocated memory will be freed and minishell will exit cleanly
void	ft_cleanup(t_token *tok, char *input, int exit_no)
{
	if (input != NULL)
		free(input);
	if (tok != NULL)
		ft_free_tok(tok);
	exit(exit_no);
}
