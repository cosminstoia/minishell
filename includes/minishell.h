/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:23:04 by gstronge          #+#    #+#             */
/*   Updated: 2024/06/26 19:18:48 by gstronge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>             //needed for error numbers/messages
# include <fcntl.h>             //needed for open/read/write
# include <stdio.h>             //needed for the readline library
# include <readline/history.h>  //needed for history function
# include <readline/readline.h> //needed for readline function
# include <signal.h>            //needed for signals
# include <stdlib.h>            //needed for malloc/free functions
# include <sys/wait.h>          //needed for wait functions

extern volatile sig_atomic_t	got_sig;

/* struct with all the variables required to execute one command */
typedef struct s_token
{
	char						**cmd;
	char						*path;
	char						*in;
	char						*out;
	char						*out_a;
	char						*heredoc;
	pid_t						pid;
}								t_token;

/* struct with the variables that stay constant no matter which command is 
being executed */
typedef struct s_cnst
{
	char						**environ;
	char						**env_p;
	char						*input;
	int							tok_num;
}								t_cnst;

/* Functions prototypes */

/* minishell.c : */
t_cnst		*ft_make_consts(t_cnst *consts, char **env);
char		*ft_return_env_var(t_cnst *consts, char *find_str);
char		**ft_make_env_path(t_token *tok, t_cnst *consts);

/* signals.c: function to handle the signals */
void		ft_handle_sig(void);

/* redirections.c: function to handle the redirections */
void		ft_redirect(t_token *tok);

/* execute.c: function to handle the execution */
void		ft_exec_cmds(t_token *tok, char *input);

/* builtins.c: functions to handle the builtin functions */
void		ft_execute(t_token *tok, char *input);
void		ft_execute_echo(t_token *tok);
void		ft_execute_cd(t_token *tok);
//void		ft_execute_export(char **args);

/* cleanup.c: functions to free allocated memory and exit minishell */
void		ft_free_splits(char **array);
void		ft_free_tok(t_token *tok, t_cnst *consts);
void		ft_free_const(t_cnst *consts);
void		ft_cleanup(t_token *tok, t_cnst *consts, int exit_no);
void		ft_exit(t_cnst *consts);

/* parsing.c: functions to parse the user input and create tokens of commands */
t_token		*ft_parse_input(t_token *tok, t_cnst *consts);
int			ft_token_num(char *input, int tok_num);
t_token		*ft_init_tok(t_token *tok, int index);
int			ft_cpy_tok_str(char *input, char *tok_str, int i);
t_token		*ft_make_toks(t_token *tok, t_cnst *consts, char *tok_str, int tok_no);

/* split.c: functions to split env PATH and commands into an array of strings*/
char		**ft_split_ms(char *str, char c);
int			ft_skip_quotes(char *str, int i);
int			ft_strnum_ms(char *str, char c, int strnum);
int			ft_strlen_ms(char *str, char c, int strlen);
int			ft_copystr_ms(char **strstr, char *str, char c, int index);
int			ft_env_var(char **strstr, char *str, char c, int index);

/* fill_tokens.c: functions to fill the tok struct with the data from input */
t_token		*ft_fill_tok(t_token *tok, t_cnst *consts,	char *tok_str, int index);
void		ft_redir_file(t_token *tok, t_cnst *consts, char *tok_str, int index);
char		*ft_cpy_redir(t_token *tok, t_cnst *consts, char *tok_str, char *str);

/* path.c functions to create the path needed by execve to execute a command */
int			ft_strcpy_ms(char *cmd, char **path);
char		*ft_path_name(char *path, char *command, char *str, char c);
int			ft_pathlen(char *env_path, char *command, int pathlen);
char		*ft_path_access(t_token *tok, t_cnst *consts, int *sub_index, int index);
void		ft_print_err(t_token *tok, t_cnst *consts, char *tok_str, char *path);
char		*ft_make_path(t_token *tok, t_cnst *consts, char *tok_str, int index);

#endif