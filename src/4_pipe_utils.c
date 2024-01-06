/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_pipe_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:27:28 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/26 10:42:47 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_cmd(t_utils *utils, t_cmd *cmd)
{
	char	**exe_cmd;
	int		i;

	i = -1;
	while (cmd->str && cmd->str[++i])
	{
		if (cmd->str[i] == '$')
			var_handling(utils, &cmd->str, i);
		else if (cmd->str[i] == '\"')
			i += d_quote_handling(utils, cmd, i);
		else if (cmd->str[i] == '\'')
			i += quote_handling(cmd, '\'', i);
	}
	exe_cmd = ft_split(cmd->str, ' ');
	return (exe_cmd);
}

int	check_heredoc(t_cmd *cmd, int *pipe_fd)
{
	int	fd;

	if (cmd->heredoc_eof)
	{
		close(pipe_fd[0]);
		fd = open("heredoc.txt", O_RDONLY);
	}
	else
		fd = pipe_fd[0];
	return (fd);
}

void	single_cmd(t_utils *utils, t_cmd *cmd)
{
	int	pid;
	int	status;

	signal(SIGINT, sigint_process);
	if (cmd->builtins == do_cd || cmd->builtins == do_exit
		|| cmd->builtins == do_export || cmd->builtins == do_unset)
	{
		g_exitnbr = cmd->builtins(utils, cmd);
		return ;
	}
	if (heredoc(utils, utils->cmds) == 130)
		return ;
	pid = fork();
	if (pid == -1)
		minishell_err(utils, "Fork", false);
	if (pid == 0)
		handle_cmd(utils, utils->cmds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exitnbr = WEXITSTATUS(status);
}
