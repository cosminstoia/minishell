/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:29:47 by cstoia            #+#    #+#             */
/*   Updated: 2024/07/17 17:00:50 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to check if there is provided an argument
static int	ft_check_argument(t_token *tok, t_cnst *consts)
{
	int		i;
	char	*equal_sign;

	if (tok->cmd[1] == NULL)
	{
		i = 0;
		while (consts->environ[i] != NULL)
		{
			equal_sign = ft_strchr(consts->environ[i], '=');
			if (equal_sign)
			{
				ft_putstr_fd("declare -x ", STDOUT_FILENO);
				ft_putstr_fd(consts->environ[i], STDOUT_FILENO);
			}
			else
			{
				ft_putstr_fd("declare -x ", STDOUT_FILENO);
				ft_putstr_fd(consts->environ[i], STDOUT_FILENO);
				ft_putstr_fd("=\"\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
			i++;
		}
		return (0);
	}
	return (1);
}

// Function to check if the variable already exists
static int	ft_check_var(t_token *tok, t_cnst *consts)
{
	int	i;

	i = 0;
	while (consts->environ[i])
	{
		if (ft_strncmp(consts->environ[i], tok->cmd[1],
				ft_strlen(tok->cmd[1])) == 0
			&& consts->environ[i][ft_strlen(tok->cmd[1])] == '=')
		{
			free(consts->environ[i]);
			break ;
		}
		i++;
	}
	return (i);
}

// Update or add the new variable to the environment array
static void	ft_add_var(t_cnst *consts, char *new_var, int i)
{
	if (consts->environ[i] == NULL)
	{
		consts->environ[i] = new_var;
		consts->environ[i + 1] = NULL;
	}
	else
		consts->environ[i] = new_var;
}

// Function to execute the "export" command
void	ft_execute_export(t_token *tok, t_cnst *consts)
{
	char	*equal_sign;
	char	*var_name;
	char	*value;
	int		i;
	char	*new_var;
	size_t	var_len;
	size_t	value_len;

	if (!ft_check_argument(tok, consts))
		return ;
	equal_sign = ft_strchr(tok->cmd[1], '=');
	if (equal_sign == NULL)
		return ;
	*equal_sign = '\0';
	var_name = tok->cmd[1];
	value = equal_sign + 1;
	i = ft_check_var(tok, consts);
	var_len = ft_strlen(var_name);
	value_len = ft_strlen(value);
	new_var = malloc(var_len + value_len + 2);
	if (new_var == NULL)
		return ;
	ft_strlcpy(new_var, var_name, var_len + 1);
	new_var[var_len] = '=';
	ft_strlcpy(new_var + var_len + 1, value, value_len + 1);
	ft_add_var(consts, new_var, i);
}

// Function to replicate the bash command exit
void	ft_execute_exit(t_token *tok, t_cnst *consts)
{
	int	exit_no;
	int	i;
	int	num_check;

	i = 4;
	exit_no = 0;
	while (consts->input[i] == ' ' || consts->input[i] == '\t')
		i++;
	num_check = i;
	while (consts->input[num_check] != '\0')
	{
		if (consts->input[num_check] != '-' && consts->input[num_check] != '+' && !(consts->input[num_check] >= '0' && consts->input[num_check] <= '9'))
		{
			printf("exit: %s: numeric argument required\n", &consts->input[i]);
			exit_no = 255;
			break ;
		}
		num_check++;
	}
	if (consts->input[num_check] == '\0')
	{
		exit_no = ft_atoi(&consts->input[i]);
		if (exit_no > 255)
			exit_no = exit_no % 256;
		if (exit_no < 0)
			exit_no = 256 + exit_no;
	}
	ft_cleanup(tok, consts, exit_no);
	exit(exit_no);
}
