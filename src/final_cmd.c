/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:53:09 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/08 12:40:17 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function to calculate how long the string will need to be after the $ symbol
 has been expanded */
int	ft_strlen_cmd(t_cnst *consts, char *cmd_str, int index, int dol_num)
{
	int	strlen_cmd;
	int	strlen_var;
	int	var_len;

	strlen_cmd = 0;
	strlen_var = 0;
	var_len = 1;
	index = 0;
	strlen_cmd = dol_num;
	while (cmd_str[dol_num + var_len] != '\0' \
	&& cmd_str[dol_num + var_len] != ' ' \
	&& cmd_str[dol_num + var_len] != '\t' \
	&& cmd_str[dol_num + var_len] != '\'' \
	&& cmd_str[dol_num + var_len] != '"')
		var_len++;
	while (cmd_str[strlen_cmd + var_len] != '\0')
		strlen_cmd++;
	while (consts->environ[index] != NULL)
	{
		if (!ft_strncmp(&cmd_str[dol_num + 1], consts->environ[index], var_len
				- 1) && (consts->environ[index][var_len - 1] == '='))
			strlen_var = ft_strlen(&consts->environ[index][var_len]);
		index++;
	}
	return (strlen_cmd + strlen_var + 1);
}

/* function that coppies the expanded variable to the command string at the
correct location in the string*/
int	ft_cpyvar(t_cnst *consts, char *cmd_str, char *cmd_new, int i)
{
	int	index;
	int	var_len;

	index = 0;
	var_len = 0;
	i = 0;
	while (cmd_str[var_len] != '\0' && cmd_str[var_len] != ' ' \
	&& cmd_str[var_len] != '\t' && cmd_str[var_len] != '\'' \
	&& cmd_str[var_len] != '"')
		var_len++;
	while (consts->environ[index] != NULL)
	{
		if (!ft_strncmp(&cmd_str[0], consts->environ[index], var_len)
			&& (consts->environ[index][var_len] == '='))
		{
			while (consts->environ[index][var_len + 1 + i] != '\0')
			{
				cmd_new[i] = consts->environ[index][var_len + 1 + i];
				i++;
			}
			break ;
		}
		index++;
	}
	return (i);
}

/* function to copy the command string up to the point where the $ symbol is */
int	ft_cpy_to_dollar(char *cmd_new, char *cmd_str, int dol_num, int i)
{
	while (i < dol_num)
	{
		cmd_new[i] = cmd_str[i];
		i++;
	}
	return (i);
}

/* function to expand the variable after the $ symbol and re-build the command
 string */
char	*ft_remake_cmd(t_token *tok, t_cnst *consts, char *cmd_str, int dol_num)
{
	char	*cmd_new;
	int		strlen;
	int		i;

	strlen = 0;
	i = 0;
	strlen = ft_strlen_cmd(consts, cmd_str, i, dol_num);
	cmd_new = (char *)malloc(strlen * sizeof(char));
	if (cmd_new == NULL)
		ft_cleanup(tok, consts, errno);
	i = ft_cpy_to_dollar(cmd_new, cmd_str, dol_num, i);
	i = i + ft_cpyvar(consts, &cmd_str[dol_num + 1], &cmd_new[i], i);
	while (cmd_str[dol_num] != '\0' && cmd_str[dol_num] != ' ' \
	&& cmd_str[dol_num] != '\t' && cmd_str[dol_num] != '\'' \
	&& cmd_str[dol_num] != '"')
		dol_num++;
	while (i < strlen)
	{
		cmd_new[i] = cmd_str[dol_num];
		i++;
		dol_num++;
	}
	free(cmd_str);
	return (cmd_new);
}
