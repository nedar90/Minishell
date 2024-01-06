/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ft_error1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:49:35 by kzhan             #+#    #+#             */
/*   Updated: 2023/09/30 14:43:47 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argument_err(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->str && cmd->str[++i])
	{
		if (cmd->str[i] == ' ')
		{
			print_err(NULL, cmd->builtin, ": too many arguments");
			return (1);
		}
	}
	return (0);
}

void	print_err(char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putendl_fd(s1, STDERR_FILENO, false);
	ft_putendl_fd(s2, STDERR_FILENO, false);
	ft_putendl_fd(s3, STDERR_FILENO, true);
}

void	ft_error(char *err, bool flag)
{
	int	len;

	len = 0;
	if (flag)
	{
		len = ft_strlen(err);
		write(STDERR_FILENO, err, len);
	}
	else
		perror(err);
}

void	minishell_err(t_utils *utils, char *err, bool flag)
{
	(void)utils;
	ft_error(err, flag);
	if (!g_exitnbr)
		g_exitnbr = EXIT_FAILURE;
	reset(utils);
}

int	heredoc_err(void)
{
	ft_putendl_fd("130", STDOUT_FILENO, true);
	g_exitnbr = EXIT_SUCCESS;
	return (0);
}
