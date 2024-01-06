/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:32:57 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 16:06:24 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ARGS_ERR	"This program does not accept argument\n"
# define PIPE_ERR	"pipe: parse error near `|'\n"
# define MALLOC_ERR	"Error while allocating memory: malloc\n"
# define TOKEN_ERR	"syntax error near unexpected token `"
# define PIPE_T_ERR	"syntax error near unexpected token `|'\n"
# define EOF_ERR	"warning: here-document delimited by end-of-file\n"

extern int	g_exitnbr;

typedef enum s_token
{
	PIPE = 1,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	D_QOUTE,
}	t_token;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_utils
{
	t_lexer			*lexer;
	struct s_cmd	*cmds;
	char			*argv;
	char			**env;
	int				pipes;
	int				*pid;
	bool			reset;
}	t_utils;

typedef struct s_cmd
{
	char			*str;
	char			*builtin;
	int				(*builtins)(t_utils *, struct s_cmd *);
	char			*heredoc_eof;
	char			*append_txt;
	t_lexer			*redirection;
	struct s_cmd	*next;
}	t_cmd;

/*  0--signal  */
int		check_signal(void);
void	sigint_heredoc(int sig);
void	sigint_process(int sig);
void	handle_signal(int sig);

/*  0--utils  */
int		init_utils(t_utils *utils);
int		init_env(t_utils *utils, char **old_env);
int		reset(t_utils *utils);
int		heredoc_err(void);
int		check_arg_err(char *arg);
int		argument_err(t_cmd *cmd);
void	ft_error(char *err, bool flag);
void	print_err(char *s1, char *s2, char *s3);
void	minishell_err(t_utils *utils, char *err, bool flag);
void	ft_free_utils(t_utils *utils);
void	ft_free(char **str);

/*  1--lexer  */
t_token	single_token(char c);
t_lexer	*creat_lexer(char **av);
t_lexer	*ls_lexernew(void *content);
char	*ft_find_word(char **env, char *word, int size);
int		skipping(char *str);
int		quote_check(char *str, char sign);
int		append_node(char *str, t_token token, t_lexer **lexer_list);
int		lexer(t_utils *utils);

/*  2--parser  */
t_cmd	*init_t_cmd(void);
void	parser(t_utils *utils, t_lexer *lexer);

/*  3--buildin/excecutor  */
char	*search_in_env(t_utils *utils, char *str);
int		do_export(t_utils *utils, struct s_cmd *cmd);
int		do_unset(t_utils *utils, struct s_cmd *cmd);
int		do_pwd(t_utils *utils, struct s_cmd *cmd);
int		do_env(t_utils *utils, struct s_cmd *cmd);
int		do_echo(t_utils *utils, struct s_cmd *cmd);
int		d_quote_handling(t_utils *utils, t_cmd *cmd, int i);
int		quote_handling(t_cmd *cmd, char c, int i);
int		do_cd(t_utils *utils, struct s_cmd *cmd);
int		update_env(t_utils *utils, char *str, int size, int end);
int		do_exit(t_utils *utils, struct s_cmd *cmd);
int		heredoc(t_utils *utils, t_cmd *cmd);

/*  3--expander  */
int		var_handling(t_utils *utils, char **str, int start);

/*  4--executer  */
char	**check_cmd(t_utils *utils, t_cmd *cmd);
int		check_heredoc(t_cmd *cmd, int *pipe_fd);
int		redirection(t_utils *utils, t_cmd *cmd);
int		do_pipe(t_utils *utils);
int		cmd_executer(t_utils *utils, char **cmd);
void	handle_cmd(t_utils	*utils, t_cmd *cmd);
void	single_cmd(t_utils *utils, t_cmd *cmd);

#endif
