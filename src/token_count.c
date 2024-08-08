/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:52:02 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/08 12:52:37 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// function that uses the input string to find the number of tokens required
int	ft_token_num(char *input, int tok_num)
{
	int	i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] != '\0')
		tok_num++;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			i = ft_check_quotes(input, i);
			i--;
		}
		else if (input[i] == '|' && input[i + 1] != '|')
			tok_num++;
		if (input[i] != '\0')
			i++;
	}
	return (tok_num);
}

// function to make sure an extra token is not counted if a pipe is found within
// quotes
int	ft_check_quotes(char *input, int i)
{
	char	quote_symb;

	quote_symb = input[i];
	i++;
	while (input[i] != '\0' && input[i] != quote_symb)
		i++;
	if (input[i] == quote_symb)
		i++;
	return (i);
}
