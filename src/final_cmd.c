/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:53:09 by gstronge          #+#    #+#             */
/*   Updated: 2024/07/18 17:35:41 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function to calculate how long the string will need to be after the $ symbol
 has been expanded */
int	ft_strlen_cmd(t_cnst *consts, char *cmd_str, int strlen, int dol_num)
{
	int	strlen_cmd;
	int	strlen_var;
	int	var_len;
	int	index;

	strlen_cmd = 0;
	strlen_var = 0;
	var_len = 1;
	index = 0;
	strlen_cmd = dol_num;
	while (cmd_str[dol_num + var_len] != '\0' && cmd_str[dol_num + var_len] != ' ' && cmd_str[dol_num + var_len] != '\t' && cmd_str[dol_num + var_len] != '\'' && cmd_str[dol_num + var_len] != '"')
		var_len++;
	while (cmd_str[strlen_cmd + var_len] != '\0')
		strlen_cmd++;
	while (consts->environ[index] != NULL)
	{
		if (!ft_strncmp(&cmd_str[dol_num + 1], consts->environ[index], var_len - 1) && (consts->environ[index][var_len - 1] == '='))
			strlen_var = ft_strlen(&consts->environ[index][var_len]);
		index++;
	}
	strlen = strlen_cmd + strlen_var + 1;
	return(strlen);
}

/* function that coppies the expanded variable to the command string at the 
correct location in the string*/
int	ft_cpyvar(t_cnst *consts, char *cmd_str, char *cmd_new)
{
	int	index;
	int	var_len;
	int	i;

	index = 0;
	var_len = 0;
	i = 0;
	while (cmd_str[var_len] != '\0' && cmd_str[var_len] != ' ' && cmd_str[var_len] != '\t' && cmd_str[var_len] != '\'' && cmd_str[var_len] != '"')
		var_len++;
	while (consts->environ[index] != NULL)
	{
		if (!ft_strncmp(&cmd_str[0], consts->environ[index], var_len) && (consts->environ[index][var_len] == '='))
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

/* function to expand the variable after the $ symbol and re-build the command 
 string */
char	*ft_remake_cmd(t_token *tok, t_cnst *consts, char *cmd_str, int dol_num)
{
	char	*cmd_new;
	int		strlen;
	int		i;

	strlen = 0;
	i = 0;
	strlen = ft_strlen_cmd(consts, cmd_str, strlen, dol_num);
	cmd_new = (char *)malloc(strlen * sizeof(char));
	if (cmd_new == NULL)
		ft_cleanup(tok, consts, errno);
	while (i < dol_num)
	{
		cmd_new[i] = cmd_str[i];
		i++;
	}
	i = i + ft_cpyvar(consts, &cmd_str[dol_num + 1], &cmd_new[i]);
	while (cmd_str[dol_num] != '\0' && cmd_str[dol_num] != ' ' && cmd_str[dol_num] != '\t' && cmd_str[dol_num] != '\''  && cmd_str[dol_num] != '"')
		dol_num++;
	while (i < strlen)
	{
		cmd_new[i] = cmd_str[dol_num];
		i++;
		dol_num++;
	}
	free(cmd_str);
	return(cmd_new);
}

/* function to convert the int of the exit code number into a string and add it
 to the existing string of the command */
char	*ft_make_exit_code(t_cnst *consts, t_token *tok_current, int index, int dol_num)
{
	char	*new_cmd;
	char	*exit_code_str;
	int		strlen;
	int		i;
	int		j;

	i = dol_num;
	j = 0;
	while (tok_current->cmd[index][i] != '\0')
		i++;
	i--;
	exit_code_str = ft_itoa(consts->exit_code);
	strlen = i + ft_strlen(exit_code_str);
	new_cmd = (char *)malloc(strlen * sizeof(char));
	if (new_cmd == NULL)
		return (NULL);
	i = 0;
	while (i < dol_num)
	{
		new_cmd[i] = tok_current->cmd[index][i];
		i++;
	}
	while (exit_code_str[j] != '\0')
	{
		new_cmd[i] = exit_code_str[j];
		i++;
		j++;
	}
	dol_num+=2;
	while (tok_current->cmd[index][dol_num] != '\0')
	{
		new_cmd[i] = tok_current->cmd[index][dol_num];
		i++;
		dol_num++;
	}
	new_cmd[i] = '\0';
	free(tok_current->cmd[index]);
	return (new_cmd);
}

/* function to check if any of the command strings have $ symbols and therefore
 need expanding */
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
				while (tok_current->cmd[index][i] != '\'')
					i++;
				i++;
			}
			else if (tok_current->cmd[index][i] == '"')
			{
				i++;
				while (tok_current->cmd[index][i] != '"')
				{
					if (tok_current->cmd[index][i] == '$')
					{
						if (tok_current->cmd[index][i + 1] == '\0' || tok_current->cmd[index][i + 1] == '"' || tok_current->cmd[index][i + 1] == ' ' || tok_current->cmd[index][i + 1] == '\t')
							i++;
						else if (tok_current->cmd[index][i + 1] == '?')
						{
							tok_current->cmd[index] = ft_make_exit_code(consts, tok_current, index, i);
							if (tok_current->cmd[index] == NULL)
								ft_cleanup(tok, consts, errno);
						}
						else
							tok_current->cmd[index] = ft_remake_cmd(tok, consts, tok_current->cmd[index], i);
						while (tok_current->cmd[index][i] != '"' && tok_current->cmd[index][i] != '$')
							i++;
					}
					else
						i++;
				}
				i++;
			}
			else if (tok_current->cmd[index][i] == '$')
			{
				if (tok_current->cmd[index][i + 1] == '\0' || tok_current->cmd[index][i + 1] == ' ' || tok_current->cmd[index][i + 1] == '\t')
					i++;
				else if (tok_current->cmd[index][i + 1] == '?')
				{
					tok_current->cmd[index] = ft_make_exit_code(consts, tok_current, index, i);
					if (tok_current->cmd[index] == NULL)
						ft_cleanup(tok, consts, errno);
				}
				else
					tok_current->cmd[index] = ft_remake_cmd(tok, consts, tok_current->cmd[index], i);
				while (tok_current->cmd[index][i] != '\0' && tok_current->cmd[index][i] != ' ' && tok_current->cmd[index][i] != '\t' && tok_current->cmd[index][i] != '\'' && tok_current->cmd[index][i] != '"' && tok_current->cmd[index][i] != '$')
					i++;
			}
			else
				i++;
		}
		index++;
	}
	return(tok_current->cmd);
}

/* function to remove quotes from the command before execution*/
char **ft_remove_quotes(char **cmd)
{
	char	quote_symb;
	int		index;
	int		i;
	int		j;

	index = 0;
	while (cmd[index])
	{
		i = 0;
		j = 0;
		while (cmd[index][i] != '\0')
		{
			if (cmd[index][i] == '"' || cmd[index][i] == '\'')
			{
				quote_symb = cmd[index][i];
				i++;
				while (cmd[index][i] != quote_symb)
				{
					cmd[index][j] = cmd[index][i];
					i++;
					j++;
				}
				i++;
			}
			else
			{
				cmd[index][j] = cmd[index][i];
				i++;
				j++;
			}
		}
		cmd[index][j] = '\0';
		index++;
	}
	return (cmd);
}
