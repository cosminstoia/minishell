/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:18:47 by gstronge          #+#    #+#             */
/*   Updated: 2024/07/08 20:54:08 by gstronge         ###   ########.fr       */
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
		if (str[j] == '>' || str[j] == '<')
		{
			while (str[j] == '>' || str[j] == '<' || str[j] == ' ')
				j++;
			while (str[j] != '\0' && str[j] != ' ')
				j++;
			while (str[j] == c)
				j++;
		}
		j = j + ft_copystr_ms(strstr, str + j, c, i);
		if (strstr[i] == NULL)
			return (NULL);
		i++;
	}
	strstr[i] = NULL;
	return (strstr);
}

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
	return(i);
}

// int	ft_check_quotes2(char *input, int i)//combine this with check_quotes in parsing.c
// {
// 	char	quote_symb;

// 	quote_symb = input[i];
// 	i++;
// 	while (input[i] != '\0' && input[i] != quote_symb)
// 		i++;
// 	if (input[i] == quote_symb)
// 		i++;
// 	return (i);
// }

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
			while (str[i] != '\0' && str[i] != c && str[i] != '>' && str[i] != '<' && str[i] != '\'' && str[i] != '"')
				i++;
		}
		else if (str[i] != c)
		{
			strnum++;
			while (str[i] != '\0' && str[i] != c && str[i] != '>' && str[i] != '<' && str[i] != '\'' && str[i] != '"')
				i++;
		}
		else if (str[i] != '\0')
			i++;
	}
	return (strnum);
}

// function to calculate how long the string should be
int	ft_strlen_ms(char *str, char c, int len)
{
	char	quote_symb;
	int 	i;

	i = 0;

	while (str[len] != '\0' && str[len] != c && str[len] != '|' )
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
	// if (str[i] == '$')
	// 	return (ft_env_var(strstr, str, c, index));
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

// function to create a string of an environment variable whenever a $
// symbol is found in the input string
int	ft_env_var(char **strstr, char *str, char c, int index)
{
	char	*temp_str;
	int		strlen;
	int		i;

	strlen = 0;
	i = 0;
	while (str[strlen] != '\0' && str[strlen] != c)
		strlen++;
	strlen++;
	temp_str = (char *)malloc(strlen * sizeof(char));
	if (temp_str == NULL)
		return (-1);
	while (i < strlen - 1)
	{
		temp_str[i] = str[i + 1]; 
		i++;
	}
	temp_str[i] = '\0';
	strstr[index] = ft_strdup(getenv(temp_str));
	free(temp_str);
	return (strlen);
}
