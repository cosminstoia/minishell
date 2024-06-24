/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:23:04 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/24 11:02:26 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>             //needed for error numbers/messages
# include <fcntl.h>             //needed of open/read/write
# include <readline/history.h>  //needed for history function
# include <readline/readline.h> //needed for readline function
# include <signal.h>            //needed for signals
# include <stdio.h>             //needed for the readline library
# include <stdlib.h>            //needed for malloc/free functions
# include <sys/wait.h>          //needed for wait functions

extern volatile sig_atomic_t	got_sig;

typedef struct s_token
{
	char						**env_p;
	char						**cmd;
	char						*path;
	char						*in;
	char						*out;
	char						*out_a;
	char						*heredoc;
	pid_t						pid;
}								t_token;

/* Functions prototypes */

/* signals.c: function to handle the signals */
void							ft_handle_sig(int signum);

/* redirections.c: function to handle the redirections */
void							ft_redirect(t_token *tok);

/* cleanup.c: functions to free allocated memory and exit minishell */
void	ft_free_splits(char **array);
void	ft_free_tok(t_token *tok);
void	ft_cleanup(t_token *tok, char *input, int exit_no);

#endif