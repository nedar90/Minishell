/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_pipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:17:08 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/30 10:27:17 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_wait(t_utils *utils)
{
	int		i;
	int		status;

	i = -1;
	while (++i <= utils->pipes)
		waitpid(utils->pid[i], &status, 0);
	if (WIFEXITED(status))
		g_exitnbr = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

void	handle_cmd(t_utils	*utils, t_cmd *cmd)
{
	char	**exe_cmd;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
	if (cmd->redirection || cmd->heredoc_eof)
		if (redirection(utils, cmd))
			exit(1);
	if (cmd->builtin)
	{
		exit_code = cmd->builtins(utils, cmd);
		exit(exit_code);
	}
	else if (cmd->str)
	{
		exe_cmd = check_cmd(utils, cmd);
		exit_code = cmd_executer(utils, exe_cmd);
		if (exit_code == 127)
			ft_error(cmd->str, false);
	}
	exit(exit_code);
}

void	do_dup(t_utils *utils, t_cmd *cmd, int *pipe_fd, int fd_in)
{
	if (fd_in)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			minishell_err(utils, "dup2", false);
	}
	close(pipe_fd[STDIN_FILENO]);
	if (cmd->next)
	{
		if (dup2(pipe_fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
			minishell_err(utils, "dup2", false);
	}
	close(pipe_fd[STDOUT_FILENO]);
	handle_cmd(utils, cmd);
}

int	do_fork(t_utils	*utils, t_cmd *cmd, int *pipe_fd, int fd_in)
{
	static int	i = 0;

	if (utils->reset == true)
	{
		i = 0;
		utils->reset = false;
	}
	utils->pid[i] = fork();
	if (utils->pid[i] == -1)
		minishell_err(utils, "fork", false);
	if (utils->pid[i] == 0)
		do_dup(utils, cmd, pipe_fd, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	do_pipe(t_utils *utils)
{
	int		pipe_fd[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (utils->cmds)
	{
		if (utils->cmds->next)
		{
			if (pipe(pipe_fd) == -1)
				minishell_err(utils, "pipe", false);
		}
		heredoc(utils, utils->cmds);
		do_fork(utils, utils->cmds, pipe_fd, fd_in);
		close(pipe_fd[1]);
		if (fd_in)
			close(fd_in);
		fd_in = check_heredoc(utils->cmds, pipe_fd);
		if (utils->cmds->next)
			utils->cmds = utils->cmds->next;
		else
			break ;
	}
	do_wait(utils);
	return (EXIT_SUCCESS);
}
