/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gstronge <gstronge@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:23:04 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/24 15:03:11 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>				//needed for error numbers/messages
# include <fcntl.h>				//needed for open/read/write
# include <stdio.h>				//needed for the readline library
# include <readline/history.h>	//needed for history function
# include <readline/readline.h>	//needed for readline function
# include <signal.h>			//needed for signals
# include <stdlib.h>			//needed for malloc/free functions
# include <sys/wait.h>			//needed for wait functions

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
	int							tok_num;
	pid_t						pid;
}								t_token;

/* Functions prototypes */

/* signals.c: function to handle the signals */
void							ft_handle_sig(int signum);

/* redirections.c: function to handle the redirections */
void							ft_redirect(t_token *tok);


/* builtins.c: functions to handle the builtin functions */
void							ft_execute_echo(char **args);
void							ft_execute_cd(char *directory);
void							ft_execute_export(char **args);

/* cleanup.c: functions to free allocated memory and exit minishell */
void	ft_free_splits(char **array);
void	ft_free_tok(t_token *tok);
void	ft_cleanup(t_token *tok, char *input, int exit_no);
void	ft_exit(char *input);

/* parsing.c: functions to parse the user input and create tokens of commands */
t_token	*ft_parse_input(t_token *tok, char *input);
int		ft_token_num(char *input, int tok_no);
t_token	*ft_init_toks(t_token *tok, int tok_num);
int		ft_cpy_tok_str(char *input, char *tok_str, int i);
t_token	*ft_make_toks(t_token *tok, char *input, char *tok_str, int tok_no);

#endif