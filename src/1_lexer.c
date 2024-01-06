/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:23:04 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 13:46:48 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	single_token(char c)
{
	int			i;
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', REDIR_OUT},
	{'<', REDIR_IN},
	};

	i = -1;
	while (++i < 3)
		if (c == token_arr[i][0])
			return (token_arr[i][1]);
	return (0);
}

static int	token_len(char *str, t_lexer **lexer_list)
{
	t_token	token;

	token = single_token(str[0]);
	if (token == REDIR_OUT && single_token(str[1]) == REDIR_OUT)
	{
		if (!append_node(NULL, APPEND, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == REDIR_IN && single_token(str[1]) == REDIR_IN)
	{
		if (!append_node(NULL, HEREDOC, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!append_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}

static int	get_words(char *str, t_lexer **lexer)
{
	int	i;

	if (!*str || !str)
		return (0);
	i = 0;
	while (str[i] && !(single_token(str[i])))
	{
		i += quote_check(&str[i], 34);
		i += quote_check(&str[i], 39);
		if (skipping(&str[i]))
			break ;
		else
			i++;
	}
	if (!append_node(ft_substr(str, 0, i), 0, lexer))
		return (-1);
	return (i);
}

int	lexer(t_utils *utils)
{
	int		i;
	int		j;

	i = 0;
	utils->lexer = NULL;
	if (!*utils->argv)
		return (0);
	while (utils->argv[i])
	{
		j = 0;
		i += skipping(&utils->argv[i]);
		if (single_token(utils->argv[i]))
			j = token_len(&(utils->argv[i]), &utils->lexer);
		else
			j = get_words(&utils->argv[i], &utils->lexer);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
