/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:20:57 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/23 16:28:07 by gstronge         ###   ########.fr       */
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
		input = readline("minishell: ");
		// ft_input_error(input);
		if (input)
			add_history(input);
		// else if (!ft_strncmp("minishell", input, 10))
		// 	ft_new_shell();
		// else
		// {
		// 	tok = ft_parse_input(tok, input);
		// 	ft_exec_cmds(tok, input);
		// 	ft_free_tok(tok);
		// }
		if (input != NULL)
			free(input);
	}
}
