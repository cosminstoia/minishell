/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:41:33 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/14 12:13:04 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

// individual parts of the struct are freed in each member of the tok array
void	ft_free_tok(t_token *tok, t_cnst *consts)
{
	int	index;

	index = 0;
	while (index < consts->tok_num)
	{
		if (tok[index].cmd)
			ft_free_splits(tok[index].cmd);
		if (tok[index].path)
			free(tok[index].path);
		if (tok[index].in)
			ft_free_splits(tok[index].in);
		if (tok[index].out)
			ft_free_splits(tok[index].out);
		if (tok[index].out_a)
			ft_free_splits(tok[index].out_a);
		if (tok[index].heredoc)
			ft_free_splits(tok[index].heredoc);
		index++;
	}
	if (tok)
		free(tok);
}

// individual parts of the consts struct are freed and then the struct itself
void	ft_free_const(t_cnst *consts)
{
	if (consts->environ != NULL)
		ft_free_splits(consts->environ);
	if (consts->env_p)
		ft_free_splits(consts->env_p);
	if (consts->input != NULL)
		free(consts->input);
	free(consts);
}

// all allocated memory will be freed and minishell will exit cleanly
void	ft_cleanup(t_token *tok, t_cnst *consts, int exit_no)
{
	if (tok != NULL)
		ft_free_tok(tok, consts);
	if (consts != NULL)
		ft_free_const(consts);
	exit(exit_no);
}
