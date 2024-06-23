/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:23:04 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/23 16:28:19 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define	MINISHELL_H

# include <errno.h>//needed for error numbers/messages
# include <signal.h>//needed for signals
# include <sys/wait.h>//needed for wait functions
# include <stdlib.h>//needed for malloc/free functions
# include <stdio.h>//needed for the readline library
# include <fcntl.h>//needed of open/read/write
# include <readline/readline.h>//needed for readline function
# include <readline/history.h>//needed for history function
# include "../libft/libft.h"

typedef struct s_token
{
	char			**env_p;
	char			**cmd;
	char			*path;
	char			*in;
	char			*out;
	char			*out_a;
	char			*heredoc;
	pid_t			pid;
}				t_token;

#endif