/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:18:47 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/08 13:39:10 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// function that splits a string into an array of strings, with a char seperator
char	**ft_split_ms(char *str, char c)
{
	char	**strstr;
	int		strnum;
	int		i;
	int		j;

	strstr = NULL;
	strnum = 0;
	i = 0;
	j = 0;
	strnum = ft_strnum_ms(str, c, strnum);
	strstr = (char **)malloc((strnum + 1) * sizeof(char *));
	if (strstr == NULL)
		return (NULL);
	while (i < strnum)
	{
		while (str[j] == c)
			j++;
		j = ft_skip_redir_split(str, j, c);
		j = j + ft_copystr_ms(strstr, str + j, c, i);
		if (strstr[i] == NULL)
			return (NULL);
		i++;
	}
	strstr[i] = NULL;
	return (strstr);
}

// function to skip redirects when splitting the string
int	ft_skip_redir_split(char *str, int j, char c)
{
	if (str[j] == '>' || str[j] == '<')
	{
		while (str[j] == '>' || str[j] == '<' || str[j] == ' ')
			j++;
		while (str[j] != '\0' && str[j] != ' ' && str[j] != '\t')
			j++;
		while (str[j] == c)
			j++;
	}
	return (j);
}

// function to calculate how long the string should be
int	ft_strlen_ms(char *str, char c, int len)
{
	char	quote_symb;

	while (str[len] != '\0' && str[len] != c && str[len] != '|')
	{
		if (str[len] == '\'' || str[len] == '"')
		{
			quote_symb = str[len];
			len++;
			while (str[len] != '\0' && str[len] != quote_symb)
				len++;
		}
		len++;
	}
	return (len);
}

// function to copy a new string from the input string and return the index of
// the input string at the location where the copying stopped (i.e. the end of
// the command or flag).
int	ft_copystr_ms(char **strstr, char *str, char c, int index)
{
	int	strlen;
	int	i;
	int	j;

	strlen = 0;
	i = 0;
	j = 0;
	strlen = ft_strlen_ms(str, c, strlen);
	strstr[index] = (char *)malloc((strlen + 1) * sizeof(char));
	if (strstr[index] == NULL)
		return (errno);
	while (i < strlen)
	{
		strstr[index][i] = str[j];
		i++;
		j++;
	}
	strstr[index][i] = '\0';
	return (j);
}
