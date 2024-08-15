/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_redir_names.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:55:25 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/15 20:07:36 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* function to update the 2D array of redirects */
char	**ft_cpy_redir(char **old_strstr, char *str)
{
	char	**new_strstr;
	int		redir_no;

	redir_no = 0;
	redir_no = ft_redirnum(old_strstr, redir_no);
	new_strstr = (char **)malloc((redir_no + 2) * sizeof(char *));
	if (new_strstr == NULL)
		return (NULL);
	ft_new_redir_str(new_strstr, str, redir_no);
	if (new_strstr == NULL)
		return (NULL);
	redir_no = 0;
	if (old_strstr)
	{
		while (old_strstr[redir_no])
		{
			new_strstr[redir_no] = old_strstr[redir_no];
			redir_no++;
		}
	}
	if (old_strstr)
		free(old_strstr);
	return (new_strstr);
}

/* function to count the number of redirects that have already been coppied */
int	ft_redirnum(char **old_strstr, int redir_no)
{
	if (old_strstr)
	{
		while (old_strstr[redir_no])
			redir_no++;
	}
	return (redir_no);
}

/* function to copy the name of the redirect to the 2D array */
char	**ft_new_redir_str(char **new_strstr, char *str, int redir_no)
{
	int	strlen;
	int	i;
	int	j;

	strlen = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i + strlen] != '\0' && str[i + strlen] != ' ')
		strlen++;
	new_strstr[redir_no] = (char *)malloc((strlen + 1) * sizeof(char));
	if (new_strstr[redir_no] == NULL)
	{
		free(new_strstr);
		return (NULL);
	}
	j = 0;
	while (str[i + j] != '\0' && str[i + j] != ' ')
	{
		new_strstr[redir_no][j] = str[i + j];
		j++;
	}
	new_strstr[redir_no][j] = '\0';
	new_strstr[redir_no + 1] = NULL;
	return (new_strstr);
}
