/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:02:49 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/08 17:48:26 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to validate the number of arguments
static int	validate_exit_arguments(t_token *tok_current)
{
	int	i;

	i = 0;
	while (tok_current->cmd[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

// Function to check if the argument is numeric and convert it to an exit code
static int	check_numeric_argument(char *arg, int *exit_no)
{
	int	i;
	int	num_check;

	i = 0;
	while (arg[i] == ' ' || arg[i] == '\t')
		i++;
	num_check = i;
	while (arg[num_check] != '\0')
	{
		if (arg[num_check] != '-' && arg[num_check] != '+'
			&& !ft_isdigit(arg[num_check]))
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				&arg[i]);
			return (1);
		}
		num_check++;
	}
	*exit_no = ft_atoi(&arg[i]);
	if (*exit_no > 255)
		*exit_no = *exit_no % 256;
	if (*exit_no < 0)
		*exit_no = 256 + *exit_no;
	return (0);
}

// Function to handle the exit and cleanup operations
static void	handle_exit(t_token *tok, t_cnst *consts, int exit_no)
{
	printf("exit\n");
	ft_cleanup(tok, consts, exit_no);
}

// Main function to execute exit
void	ft_execute_exit(t_token *tok, t_cnst *consts, t_token *tok_current)
{
	int	exit_no;

	exit_no = 0;
	if (tok_current->cmd[1] == NULL)
		handle_exit(tok, consts, exit_no);
	if (check_numeric_argument(tok_current->cmd[1], &exit_no))
	{
		ft_cleanup(tok, consts, 255);
		return ;
	}
	else if (validate_exit_arguments(tok_current))
	{
		consts->exit_code = 1;
		return ;
	}
	else
		handle_exit(tok, consts, exit_no);
}
