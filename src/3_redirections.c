/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_redirections.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:52:10 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 14:50:48 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_open(t_utils *utils, t_lexer *redirection)
{
	int	fd;

	if (redirection->token == APPEND)
		fd = open(redirection->str,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redirection->token == REDIR_OUT)
		fd = open(redirection->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(redirection->str, O_RDONLY);
	if (fd == -1)
		minishell_err(utils, redirection->str, false);
	return (fd);
}

int	heredoc_redir(t_utils *utils)
{
	int	fd;

	fd = open("heredoc.txt", O_RDONLY);
	if (fd == -1)
		minishell_err(utils, "heredoc", false);
	if (dup2(fd, STDIN_FILENO) == -1)
		minishell_err(utils, "dup2", false);
	if (fd)
		close(fd);
	return (EXIT_SUCCESS);
}

int	redirection(t_utils *utils, t_cmd *cmd)
{
	int		fd;

	if (cmd->heredoc_eof)
		heredoc_redir(utils);
	while (cmd->redirection)
	{
		fd = do_open(utils, cmd->redirection);
		if (cmd->redirection->token == REDIR_IN && fd)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				minishell_err(utils, "dup2", false);
		}
		else if ((cmd->redirection->token == REDIR_OUT
				|| cmd->redirection->token == APPEND) && fd)
		{
			if (dup2(fd, STDOUT_FILENO) == -1)
				minishell_err(utils, "dup2", false);
		}
		if (fd)
			close(fd);
		cmd->redirection = cmd->redirection->next;
	}
	return (EXIT_SUCCESS);
}
