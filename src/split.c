/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:18:47 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/25 15:19:08 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	ft_skip_redir(char *str, int i)
{
	while (str[i] == '>' || str[i] == '<' || str[i] == ' ')
		i++;
	if (str[i] == '\'' || str[i] == '"')
		i = ft_skip_quotes(str, i);
	else
	{
		while (str[i] == ' ')
			i++;
		while (str[i] != '\0' && str[i] != ' ')
			i++;
	}
	return(i);
}

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
			strnum++;
			i = ft_skip_quotes(str, i);
		}
		else if (str[i] != c)
		{
			strnum++;
			while (str[i] != '\0' && str[i] != c && str[i] != '>' && str[i] != '<' && str[i] != '\'' & str[i] != '"')
				i++;
		}
		if (str[i] != '\0')
			i++;
	}
	return (strnum);
}

int	ft_strlen_ms(char *str, char c, int strlen)
{
	if (str[strlen] == '\'')
	{
		while (str[strlen + 1] != '\'' && str[strlen + 1] != '\0')
			strlen++;
	}
	else if (str[strlen] == '"')
	{
		while (str[strlen + 1] != '"' && str[strlen + 1] != '\0')
			strlen++;
	}
	else
	{
		while (str[strlen] != c && str[strlen] != '\0')
			strlen++;
	}
	return (strlen);
}

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
	if (str[i] == '\'' || str[i] == '"')
		j++;
	while (i < strlen)
	{
		strstr[index][i] = str[j];
		i++;
		j++;
	}
	strstr[index][i] = '\0';
	if (j > i)
		j++;
	return (j);
}
