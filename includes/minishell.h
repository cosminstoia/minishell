/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cstoia <cstoia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 16:23:04 by gstronge          #+#    #+#             */
/*   Updated: 2024/08/12 17:49:04 by cstoia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>             //needed for the readline library
# include <errno.h> 			//needed for error numbers/messages
# include <fcntl.h> 			//needed for open/read/write
# include <limits.h>
# include <readline/history.h>  //needed for history function
# include <readline/readline.h> //needed for readline function
# include <signal.h>            //needed for signals
# include <stdlib.h>            //needed for malloc/free functions
# include <sys/wait.h>          //needed for wait functions
# include <termios.h>

int			g_got_sig;

/* struct with all the variables required to execute one command */
typedef struct s_token
{
	char	**cmd;
	char	*path;
	char	*in;
	char	*out;
	char	*out_a;
	char	*heredoc;
	int		input_fd;
	pid_t	pid;
}			t_token;

/* struct with the variables that stay constant no matter which command is
being executed */
typedef struct s_cnst
{
	char	**environ;
	char	**env_p;
	char	*input;
	int		tok_num;
	int		exit_code;
}			t_cnst;

/* Functions prototypes */

/* builtins_exec.c: functions to execute the builtin functions */
void		ft_execute_builtins(t_token *tok, t_cnst *consts, int index,
				int output_fd);
int			ft_is_builtin(char *cmd);

/* builtins.c: functions to handle the builtin functions */
void		ft_execute_echo(t_token *tok, t_cnst *consts, int output_fd);
void		ft_execute_pwd(t_cnst *consts, int output_fd);
void		ft_execute_env(t_cnst *consts, int output_fd);
char		*ft_return_env_var(t_cnst *consts, char *find_str);

/* cd.c: file that contains functions used for cd command */
void		ft_execute_cd(t_token *tok, t_cnst *consts);

/* cleanup.c: functions to free allocated memory and exit minishell */
void		ft_free_splits(char **array);
void		ft_free_tok(t_token *tok, t_cnst *consts);
void		ft_free_const(t_cnst *consts);
void		ft_cleanup(t_token *tok, t_cnst *consts, int exit_no);

/* execute_utils.c: function to handle the execution */
void		ft_wait(t_token *tok, t_cnst *consts);
void		ft_execute_child(t_token *tok, t_cnst *consts, int index);
void		ft_handle_red_no_arg(t_token *tok, t_cnst *consts, int index);

/* execute.c: function to handle the execution */
void		ft_execute(t_token *tok, t_cnst *consts);

/* exit.c: function to handle the exit function */
void		ft_execute_exit(t_token *tok, t_cnst *consts, t_token *tok_current);

/* expand_dollar.c: functions to expand dollar symbols in the command string */
char		**ft_expand_dollar(t_token *tok, t_cnst *consts,
				t_token *tok_current);
int			ft_if_dollar(t_token *tok, t_cnst *consts, char **cmd_current_ptr,
				int i);
char		*ft_if_questmark(t_token *tok, t_cnst *consts, char *cmd_current,
				int i);
int			ft_if_dbl_quote(t_token *tok, t_cnst *consts,
				char **cmd_current_ptr, int i);

/* expand_quotes_exit_code.c: functions to expand quotes and to handle the exit
code in the command string */
char		**ft_remove_quotes(char **cmd);
char		**ft_copy_quoteless(char **cmd, int index, int i, int j);
char		*ft_make_exit_code(t_cnst *consts, char *cmd_current, int dol_num);
int			ft_cpy_to_exit_code(char *new_cmd, char *cmd_current,
				char *exit_code_str, int dol_num);

/* export_utils.c: function to handle the export utility functions */
int			ft_check_argument(t_token *tok, t_cnst *consts);
int			ft_check_var(t_token *tok, t_cnst *consts);
void		ft_add_var(t_cnst *consts, char *new_var, int i);
char		**ft_realloc_env(t_token *tok, t_cnst *consts);

/* export.c: function to handle the export utility functions */
void		ft_execute_export(t_token *tok, t_token *tok_current,
				t_cnst *consts);

/* fill_tokens.c: functions to fill the tok struct with the data from input */
t_token		*ft_fill_tok(t_token *tok, t_cnst *consts, char *tok_str,
				int index);
void		ft_redir_file(t_token *tok, t_cnst *consts, char *tok_str,
				int index);
int			ft_fill_redirs(t_token *tok, t_cnst *consts, char *tok_str,
				int index);
char		*ft_cpy_redir(t_token *tok, t_cnst *consts, char *tok_str,
				char *str);

/* final_cmd.c functions to finalise the cmd strings before execution */
int			ft_strlen_cmd(t_cnst *consts, char *cmd_str, int index,
				int dol_num);
int			ft_cpyvar(t_cnst *consts, char *cmd_str, char *cmd_new, int i);
int			ft_cpy_to_dollar(char *cmd_new, char *cmd_str, int dol_num, int i);
char		*ft_remake_cmd(t_token *tok, t_cnst *consts, char *cmd_str,
				int dol_num);

/* input_error.c: functions to check if the user input is incorrect */
int			ft_quotes_close(char *input);
char		ft_no_redir_name(char *input, char err_char, int i);
char		ft_redir_err_char(char *input, char err_char, int i);
char		ft_redir_error(char *input, char err_char);
char		ft_only_pipe(char *input, char err_char);

/* heredoc.c */
int			ft_handle_heredoc(t_token *tok, t_cnst *consts, int in_fd);

/* minishell.c : */
t_cnst		*ft_make_consts(t_cnst *consts, char **env);
char		**ft_make_env_path(t_token *tok, t_cnst *consts);
int			ft_input_error(t_cnst *consts, char *input);
void		ft_use_input(t_token *tok, t_cnst *consts);

/* parsing.c: functions to parse the user input and create tokens of commands */
t_token		*ft_parse_input(t_token *tok, t_cnst *consts);
t_token		*ft_init_tok(t_token *tok, int index);
int			ft_cpy_tok_str(char *input, char *tok_str, int i, int len);
int			ft_strlen_tokstr(char *input, int len, int i);
t_token		*ft_make_toks(t_token *tok, t_cnst *consts, char *tok_str,
				int tok_no);

/* path.c functions to create the path needed by execve to execute a command */
int			ft_strcpy_ms(char *cmd, char **path);
char		*ft_path_name(char *path, char *command, char *str, char c);
int			ft_pathlen(char *env_path, char *command, int pathlen);
char		*ft_path_access(t_token *tok, t_cnst *consts, int *sub_index,
				int index);
char		*ft_make_path(t_token *tok, t_cnst *consts, int index);

/* path_cont.c additional functions to create the path */
char		*ft_path_is_cmd(t_token *tok, t_cnst *consts, int index);
void		ft_cmd_not_fnd(t_token *tok, t_cnst *consts, int index);

/* redirections_utils.c: function to handle the redirections */
int			ft_handle_infile(t_token *tok, t_cnst *consts, int in_fd);
int			ft_redirect(t_token *tok, t_cnst *consts, int *pipefd, int index);
int			ft_handle_outfile(t_token *tok, t_cnst *consts, int out_fd);

/* redirections.c: function to handle the redirections */
int			ft_handle_append(t_token *tok, t_cnst *consts, int out_fd);

/* signals.c: function to handle the signals */
void		ft_handle_sig(void);
void		ft_handle_sig_heredoc(void);

/* split.c: functions to split env PATH and commands into an array of strings */
char		**ft_split_ms(char *str, char c);
int			ft_skip_redir_split(char *str, int j, char c);
int			ft_strlen_ms(char *str, char c, int strlen);
int			ft_copystr_ms(char **strstr, char *str, char c, int index);

/* split_cont.c: additional functions to split env PATH and commands */
int			ft_skip_quotes(char *str, int i);
int			ft_skip_redir(char *str, int i);
int			ft_if_delim(char *str, int *strnum, char c, int i);
int			ft_strnum_ms(char *str, char c, int strnum);

/* token_count.c: functions to count the number of tokens */
int			ft_check_quotes(char *input, int i);
int			ft_token_num(char *input, int tok_num);

/* unset.c functions to execute the unset function */
void		ft_execute_unset(t_token *tok, t_cnst *consts);

#endif