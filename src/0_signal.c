/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:40:43 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 13:43:08 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc(int sig)
{
	(void)sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_exitnbr = 130;
}

void	sigint_process(int sig)
{
	(void) sig;
	ft_putendl_fd("", STDOUT_FILENO, true);
	g_exitnbr = 130;
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO, true);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exitnbr = 130;
	}
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO, true);
		g_exitnbr = 131;
	}
}

int	check_signal(void)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	return (EXIT_SUCCESS);
}
