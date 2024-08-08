/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:29 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/08 13:43:44 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// function to move the index to the closing quote symbol when an opening
// quote symbol is found in the input string
int	ft_skip_quotes(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'' && str[i] != '\0')
			i++;
	}
	if (str[i] == '"')
	{
		i++;
		while (str[i] != '"' && str[i] != '\0')
			i++;
	}
	if (str[i] != '\0')
		i++;
	return (i);
}

// function to move the index to the end of the filename when a redirection
// symbol is found in the input string
int	ft_skip_redir(char *str, int i)
{
	while (str[i] == '>' || str[i] == '<' || str[i] == ' ')
		i++;
	if (str[i] == '\'' || str[i] == '"')
		i = ft_skip_quotes(str, i);
	else
	{
		while (str[i] != '\0' && str[i] != ' ')
			i++;
	}
	return (i);
}

// function to add a strnum and skip the remainig characters if the delimiter is
// found
int	ft_if_delim(char *str, int *strnum, char c, int i)
{
	(*strnum)++;
	while (str[i] != '\0' && str[i] != c && str[i] != '>' && str[i] != '<'
		&& str[i] != '\'' && str[i] != '"')
		i++;
	return (i);
}

// function to count the number of strings that should be included in the array
int	ft_strnum_ms(char *str, char c, int strnum)
{
	int	i;

	i = 0;
	while (str[i] == c)
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
			i = ft_skip_redir(str, i);
		else if (str[i] == '\'' || str[i] == '"')
		{
			if (i == 0 || str[i - 1] == c)
				strnum++;
			i = ft_check_quotes(str, i);
			while (str[i] != '\0' && str[i] != c && str[i] != '>'
				&& str[i] != '<' && str[i] != '\'' && str[i] != '"')
				i++;
		}
		else if (str[i] != c)
			i = ft_if_delim(str, &strnum, c, i);
		else if (str[i] != '\0')
			i++;
	}
	return (strnum);
}
