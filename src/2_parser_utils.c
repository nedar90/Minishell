/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 15:09:03 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/12 14:23:06 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_t_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_error(MALLOC_ERR, true);
	cmd->str = NULL;
	cmd->builtin = NULL;
	cmd->builtins = NULL;
	cmd->heredoc_eof = NULL;
	cmd->append_txt = NULL;
	cmd->redirection = NULL;
	cmd->next = NULL;
	return (cmd);
}
