/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 13:37:09 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/22 15:50:51 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free (str[i]);
	free(str);
}

void	ft_free_lexer(t_lexer *lexer)
{
	void	*lexer_tmp;

	if (!lexer)
		return ;
	while (lexer)
	{
		lexer_tmp = lexer->next;
		free(lexer->str);
		free(lexer);
		lexer = lexer_tmp;
	}
}

void	ft_free_cmds(t_cmd *cmds)
{
	void	*cmd_tmp;

	if (!cmds)
		return ;
	while (cmds)
	{
		cmd_tmp = cmds->next;
		if (cmds->heredoc_eof)
			free(cmds->heredoc_eof);
		if (cmds->builtin)
			free(cmds->builtin);
		if (cmds->str)
			free(cmds->str);
		if (cmds->redirection)
			ft_free_lexer(cmds->redirection);
		free(cmds);
		cmds = cmd_tmp;
	}
}

void	ft_free_utils(t_utils *utils)
{
	if (utils->pid)
		free(utils->pid);
	if (utils->lexer)
		ft_free_lexer(utils->lexer);
	if (utils->cmds)
		ft_free_cmds(utils->cmds);
}
