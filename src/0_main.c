/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:22:08 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/26 10:29:29 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_utils *utils);

int		g_exitnbr = 0;

int	reset(t_utils *utils)
{
	if (utils)
		ft_free_utils(utils);
	utils->reset = true;
	minishell_loop(utils);
	return (1);
}

int	reset_g_exitnbr(t_utils *utils)
{
	if (g_exitnbr == 130)
	{
		if (!ft_strncmp(utils->argv, "echo $?", 7))
			return (heredoc_err());
		g_exitnbr = EXIT_SUCCESS;
	}
	return (1);
}

int	minishell_loop(t_utils *utils)
{
	if (check_signal())
		minishell_err(utils, "signal", false);
	if (init_utils(utils))
		minishell_loop(utils);
	parser(utils, utils->lexer);
	if (reset_g_exitnbr(utils))
	{
		if (signal(SIGQUIT, handle_signal) == SIG_ERR)
			minishell_err(utils, "signal", false);
		if (!utils->pipes)
			single_cmd(utils, utils->cmds);
		else
			do_pipe(utils);
	}
	unlink("heredoc.txt");
	reset(utils);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_utils	utils;

	if (ac != 1 || av[1])
	{
		ft_error(ARGS_ERR, true);
		exit(EXIT_FAILURE);
	}
	init_env(&utils, env);
	utils.reset = false;
	minishell_loop(&utils);
	rl_clear_history();
	return (g_exitnbr);
}
