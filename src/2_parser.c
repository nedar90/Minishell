/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:32:14 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 14:23:08 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	(*find_builtin(char *cmd))(t_utils *util, struct s_cmd *cmd)
{
	int			i;
	static void	*builtins[7][2] = {
	{"echo", do_echo},
	{"cd", do_cd},
	{"pwd", do_pwd},
	{"export", do_export},
	{"unset", do_unset},
	{"env", do_env},
	{"exit", do_exit},
	};

	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(cmd, builtins[i][0], ft_strlen(builtins[i][0])))
		{
			if (cmd[(ft_strlen(builtins[i][0]))]
				&& cmd[(ft_strlen(builtins[i][0]))] != ' ')
				return (0);
			return (builtins[i][1]);
		}
	}
	return (0);
}

static void	check_word(t_cmd *cmd, t_lexer *lexer)
{
	int	(*built_func)(t_utils *util, struct s_cmd *cmd);

	built_func = find_builtin(lexer->str);
	if (*built_func)
	{
		cmd->builtin = ft_strdup(lexer->str);
		cmd->builtins = built_func;
	}
	else
	{
		if (!cmd->str)
			cmd->str = ft_strdup(lexer->str);
		else
		{
			cmd->str = ft_strjoin(cmd->str, " ");
			cmd->str = ft_strjoin(cmd->str, lexer->str);
		}
	}
}

static int	check_token(t_utils *utils, t_cmd *cmd, t_lexer *lexer)
{
	if (lexer->next->token)
		minishell_err(utils, TOKEN_ERR, true);
	if (lexer->token == REDIR_IN
		|| lexer->token == APPEND
		|| lexer->token == REDIR_OUT)
	{
		if (lexer->next->str[0] == '$')
			minishell_err(utils, "$: ambiguous redirect\n", true);
		append_node(ft_strdup(lexer->next->str), lexer->token, \
		&cmd->redirection);
	}
	if (lexer->token == HEREDOC)
		cmd->heredoc_eof = ft_strdup(lexer->next->str);
	return (1);
}

void	parser(t_utils *utils, t_lexer *lexer)
{
	t_cmd	*cmd;

	cmd = init_t_cmd();
	utils->cmds = cmd;
	while (lexer)
	{
		if (!lexer->str)
		{
			if (lexer->token == PIPE)
			{
				if (lexer->next->token)
					minishell_err(utils, PIPE_T_ERR, true);
				cmd->next = init_t_cmd();
				cmd = cmd->next;
				lexer = lexer->next;
				continue ;
			}
			if (check_token(utils, cmd, lexer))
				lexer = lexer->next;
		}
		else
			check_word(cmd, lexer);
		lexer = lexer->next;
	}
}
