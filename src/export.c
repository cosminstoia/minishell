/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:29:47 by cstoia            #+#    #+#             */
/*   Updated: 2024/08/12 12:49:59 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_handle_no_equal_sign(t_token *tok, t_cnst *consts)
{
	int	i;

	i = 0;
	while (consts->environ[i])
		i++;
	consts->environ[i] = ft_strdup(tok->cmd[1]);
	if (consts->environ[i] == NULL)
		ft_cleanup(tok, consts, errno);
}

static void	ft_add_or_update_var(t_token *tok, t_cnst *consts, char *var_name,
		char *value)
{
	int		i;
	size_t	var_len;
	size_t	value_len;
	char	*new_var;

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

// Function to execute the "export" command
void	ft_execute_export(t_token *tok, t_token *tok_current, t_cnst *consts)
{
	char	*equal_sign;
	char	*var_name;
	char	*value;

	if (!ft_check_argument(tok_current, consts))
		return ;
	consts->environ = ft_realloc_env(tok_current, consts);
	equal_sign = ft_strchr(tok_current->cmd[1], '=');
	if (equal_sign == NULL)
	{
		ft_handle_no_equal_sign(tok_current, consts);
		return ;
	}
	*equal_sign = '\0';
	var_name = tok_current->cmd[1];
	value = equal_sign + 1;
	ft_add_or_update_var(tok_current, consts, var_name, value);
	if (ft_strncmp(tok_current->cmd[1], "PATH", 4) == 0)
		consts->env_p = ft_make_env_path(tok, consts);
	consts->exit_code = 0;
}
