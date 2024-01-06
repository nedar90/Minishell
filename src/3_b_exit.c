/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_b_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 14:33:41 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 12:46:05 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

int	do_exit(t_utils *utils, struct s_cmd *cmd)
{
	int		exit_code;

	ft_putendl_fd("exit", STDERR_FILENO, true);
	if (!cmd->str || !*cmd->str)
		exit_code = EXIT_SUCCESS;
	else if (ft_isdigit(cmd->str))
		exit_code = ft_atoi(cmd->str);
	else if (argument_err(cmd))
		exit_code = 1;
	else
	{
		print_err("exit: ", cmd->str, ": numeric argument required");
		exit_code = 255;
	}
	ft_free(utils->env);
	ft_free_utils(utils);
	exit (exit_code);
}
