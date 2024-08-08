/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:28:14 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/08 15:03:39 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function to check if any of the command strings have $ symbols and if so, to
do the expansion of the environment variables */
char	**ft_expand_dollar(t_token *tok, t_cnst *consts, t_token *tok_current)
{
	int	index;
	int	i;

	index = 0;
	while (tok_current->cmd[index] != NULL)
	{
		i = 0;
		while (tok_current->cmd[index][i] != '\0')
		{
			if (tok_current->cmd[index][i] == '\'')
			{
				i++;
				while (tok_current->cmd[index][i++] != '\'')
					;
			}
			else if (tok_current->cmd[index][i] == '"')
				i = ft_if_dbl_quote(tok, consts, &(tok_current->cmd[index]), i);
			else if (tok_current->cmd[index][i] == '$')
				i = ft_if_dollar(tok, consts, &(tok_current->cmd[index]), i);
			else
				i++;
		}
		index++;
	}
	return (tok_current->cmd);
}

/* function to rebuild the command string if a $ symbol is found */
int	ft_if_dollar(t_token *tok, t_cnst *consts, char **cmd_current_ptr, int i)
{
	char	*cmd_current;

	cmd_current = *cmd_current_ptr;
	if (cmd_current[i + 1] == '\0' || cmd_current[i + 1] == ' ' \
			|| cmd_current[i + 1] == '\t')
		i++;
	else if (cmd_current[i + 1] == '?')
	{
		cmd_current = ft_make_exit_code(consts, cmd_current, i);
		if (cmd_current == NULL)
			ft_cleanup(tok, consts, errno);
	}
	else
	{
		cmd_current = ft_remake_cmd(tok, consts, cmd_current, i);
	}
	while (cmd_current[i] != '\0' && cmd_current[i] != ' ' \
		&& cmd_current[i] != '\t' && cmd_current[i] != '\'' \
		&& cmd_current[i] != '"' && cmd_current[i] != '$')
		i++;
	*cmd_current_ptr = cmd_current;
	return (i);
}

/* function to rebuild the command string if a ? symbol is found after the $ */
char	*ft_if_questmark(t_token *tok, t_cnst *consts, char *cmd_current, int i)
{
	cmd_current = ft_make_exit_code(consts, cmd_current, i);
	if (cmd_current == NULL)
		ft_cleanup(tok, consts, errno);
	return (cmd_current);
}

/* function to rebuild the command string if double quotes are found */
int	ft_if_dbl_quote(t_token *tok, t_cnst *consts, char **cmd_current_ptr, int i)
{
	char	*cmd_current;

	cmd_current = *cmd_current_ptr;
	i++;
	while (cmd_current[i] != '"')
	{
		if (cmd_current[i] == '$')
		{
			if (cmd_current[i + 1] == '\0' || cmd_current[i + 1] == '"'
				|| cmd_current[i + 1] == ' ' || cmd_current[i + 1] == '\t')
				i++;
			else if (cmd_current[i + 1] == '?')
				cmd_current = ft_if_questmark(tok, consts, cmd_current, i);
			else
				cmd_current = ft_remake_cmd(tok, consts, cmd_current, i);
			while (cmd_current[i] != '"' && cmd_current[i] != '$')
				i++;
		}
		else
			i++;
	}
	*cmd_current_ptr = cmd_current;
	i++;
	return (i);
}
