/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_lexer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:36:02 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/30 10:51:11 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*ft_lstnew(char *str, t_token token)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->str = str;
	node->token = token;
	node->next = NULL;
	return (node);
}

static void	ft_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*node;

	if (!*lst)
		*lst = new;
	else
	{
		node = *lst;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

int	append_node(char *str, t_token token, t_lexer **lexer)
{
	t_lexer	*node;

	node = ft_lstnew(str, token);
	if (!node)
		return (-1);
	ft_lstadd_back(lexer, node);
	return (1);
}

int	skipping(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

int	quote_check(char *str, char quotesign)
{
	int		i;

	i = 0;
	if (str[i] == quotesign && !(single_token(str[i])))
	{
		i++;
		while (str[i] && str[i] != quotesign)
			i++;
		i++;
	}
	return (i);
}
