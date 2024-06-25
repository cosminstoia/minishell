/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:20:57 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/25 19:07:38 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tok;

	tok = NULL;
	while (1)
	{
		ft_handle_sig();
		input = readline("minishell: ");
		if (input == NULL)
			break ;
		if (input)
		{
			add_history(input);
			// ft_input_error(input);
			// if (!ft_strncmp("minishell", input, 10))
			// 	ft_new_shell();
			if (!ft_strncmp("exit", input, 4))
				ft_exit(input);
			else
			{
				tok = ft_parse_input(tok, input);
				ft_exec_cmds(tok, input);
				ft_free_tok(tok);
			}
		}
		if (input != NULL)
			free(input);
	}
}
