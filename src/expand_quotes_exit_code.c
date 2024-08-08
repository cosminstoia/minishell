/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:25:52 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/08 12:37:07 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function to remove quotes from the command before execution */
char	**ft_remove_quotes(char **cmd)
{
	int	index;
	int	i;
	int	j;

	index = 0;
	while (cmd[index])
	{
		i = 0;
		j = 0;
		cmd = ft_copy_quoteless(cmd, index, i, j);
		index++;
	}
	return (cmd);
}

/* function to copy the string but with the quotation marks removed */
char	**ft_copy_quoteless(char **cmd, int index, int i, int j)
{
	char	quote_symb;

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
	return (cmd);
}

/* function to convert the int of the exit code number into a string and add it
 to the existing string of the command */
char	*ft_make_exit_code(t_cnst *consts, char *cmd_current, int dol_num)
{
	char	*new_cmd;
	char	*exit_code_str;
	int		strlen;
	int		i;

	i = dol_num;
	while (cmd_current[i] != '\0')
		i++;
	i--;
	exit_code_str = ft_itoa(consts->exit_code);
	strlen = i + ft_strlen(exit_code_str);
	new_cmd = (char *)malloc(strlen * sizeof(char));
	if (new_cmd == NULL)
		return (NULL);
	i = ft_cpy_to_exit_code(new_cmd, cmd_current, exit_code_str, dol_num);
	dol_num += 2;
	while (cmd_current[dol_num] != '\0')
	{
		new_cmd[i] = cmd_current[dol_num];
		i++;
		dol_num++;
	}
	new_cmd[i] = '\0';
	free(cmd_current);
	return (new_cmd);
}

/* function to copy the command string up to the point where the exit code will 
be */
int	ft_cpy_to_exit_code(char *new_cmd, char *cmd_current, \
char *exit_code_str, int dol_num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < dol_num)
	{
		new_cmd[i] = cmd_current[i];
		i++;
	}
	while (exit_code_str[j] != '\0')
	{
		new_cmd[i] = exit_code_str[j];
		i++;
		j++;
	}
	return (i);
}
