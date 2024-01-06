/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_b_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:09:09 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 12:51:17 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_pwd(t_utils *utils, struct s_cmd *cmd)
{
	(void)cmd;
	(void)utils;
	ft_putendl_fd(getcwd(NULL, 0), STDOUT_FILENO, true);
	return (EXIT_SUCCESS);
}
