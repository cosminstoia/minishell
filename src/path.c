/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:29:13 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/24 19:33:35 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// function to copy the command name to the path variable in the struct
int		ft_strcpy_ms(char *cmd, char **path)
{
	int	strlen;

	strlen = 0;
	while (cmd[strlen] != '\0')
		strlen++;
	*path = (char *)malloc((strlen + 1) * sizeof(char));
	if (*path == NULL)
		return (-1);
	(*path)[strlen] = '\0';
	while (strlen > 0)
	{
		strlen--;
		(*path)[strlen] = cmd[strlen];
	}
	return (0);
}

// function that coppies the env PATH and command name to a combined string 
char	*ft_path_name(char *path, char *command, char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i] != '\0')
	{
		str[i] = path[i];
		i++;
	}
	str[i] = c;
	i++;
	while (command[j] != '\0')
	{
		str[i + j] = command[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

// function to calculate the length of a string that would combine an env PATH
// string with the command name
int	ft_pathlen(char *env_path, char *command, int pathlen)
{
	int	i;

	i = 0;
	while (env_path[pathlen] != '\0')
		pathlen++;
	pathlen++;
	while (command[i] != '\0')
	{
		pathlen++;
		i++;
	}
	pathlen++;
	return (pathlen);
}

// function to make a string that combines the each env PATH with the command
// name, and then checks to see if the executable is found there and the shell
// has access to execute the command 
char	*ft_path_access(t_token *tok, int *sub_index, int index)
{
	int	pathlen;

	while (tok[index].env_p[*sub_index] != NULL)
	{
		pathlen = 0;
		if (tok[index].path != NULL)
			free(tok[index].path);
		pathlen = ft_pathlen(tok[index].env_p[*sub_index], tok[index].cmd[0], pathlen);
		tok[index].path = (char *)malloc(pathlen * sizeof(char));
		if (tok[index].path == NULL)
		{
			*sub_index = -1;
			return (tok[index].path);
		}
		tok[index].path = ft_path_name(tok[index].env_p[*sub_index], tok[index].cmd[0], tok[index].path, '/');
		if (access(tok[index].path, F_OK | X_OK) == 0)
			break ;
		*sub_index = *sub_index + 1;
	}
	return (tok[index].path);
}

// function to print an error message if all potential path locations have been
// tested and none resulted in an executable file
void	ft_print_error(t_token *tok, char *input, char *tok_str, char *path)
{
	char	*error;
	int		pathlen;

	pathlen = 0;
	pathlen = ft_pathlen("command not found:", path, pathlen);
	error = (char *)malloc(pathlen * sizeof(char));
	if (error == NULL)
	{
		free(tok_str);
		ft_cleanup(tok, input, errno);
	}
	error = ft_path_name("command not found:", path, error, ' ');
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	free(error);
}

// function to create a path to be used by execve to execute the command
char	*ft_create_path(t_token *tok, char *input, char *tok_str, int index)
{
	int	sub_index;
	int	error;

	sub_index = 0;
	tok[index].path = ft_path_access(tok, &sub_index, index);
	if (sub_index == -1)
	{
		free(tok_str);			
		ft_cleanup(tok, input, errno);
	}
	if (tok[index].env_p[sub_index] == NULL)
	{
		free(tok[index].path);
		error = ft_strcpy_ms(tok[index].cmd[0], &tok[index].path);
		if (error == -1)
		{
			free(tok_str);
			ft_cleanup(tok, input, errno);
		}
		if (access(tok[index].cmd[0], X_OK) == -1)
			ft_print_error(tok, input, tok_str, tok[index].path);
	}
	return (tok[index].path);
}
