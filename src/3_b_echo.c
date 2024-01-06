/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_b_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:27:40 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 15:03:42 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*n_edgecase_util(t_cmd *cmd)
{
	int		i;
	char	*first;

	i = -1;
	first = cmd->str;
	while (cmd->str[++i])
	{
		if (cmd->str[i - 1] == ' ')
			first = &cmd->str[i];
		if (cmd->str[i] == '-' && cmd->str[i + 1] == 'n')
		{
			i++;
			while (cmd->str[i] == 'n')
				i++;
			if (!cmd->str[i])
				return (NULL);
			else if (cmd->str[i] != ' ')
				break ;
		}
		else
			break ;
	}
	return (first);
}

static int	n_edgecase(t_cmd *cmd)
{
	char	*first;

	first = n_edgecase_util(cmd);
	if (!*first)
		return (0);
	first = ft_strdup(first);
	free(cmd->str);
	cmd->str = first;
	return (1);
}

int	quote_handling(t_cmd *cmd, char c, int i)
{
	int	j;
	int	len;

	j = 1;
	len = 0;
	while (cmd->str[i + j] && cmd->str[i + j] != c)
	{
		cmd->str[i] = cmd->str[i + j];
		i++;
		len++;
	}
	if (cmd->str[i + j] && cmd->str[i + j] == c)
		j++;
	while (cmd->str[i + j])
	{
		cmd->str[i] = cmd->str[i + j];
		i++;
	}
	cmd->str[i] = '\0';
	return (len - 1);
}

int	d_quote_handling(t_utils *utils, t_cmd *cmd, int i)
{
	int	start;

	start = 1;
	while (cmd->str[i + start] && cmd->str[i + start] != '\"')
	{
		if (cmd->str[i + start] == '$')
			var_handling(utils, &cmd->str, start + i);
		start++;
	}
	return (quote_handling(cmd, '\"', i));
}

int	do_echo(t_utils *utils, struct s_cmd *cmd)
{
	bool	flag;
	int		i;

	(void)(utils);
	flag = true;
	if (!ft_strncmp(cmd->str, "-n", 2)
		&& n_edgecase(cmd))
		flag = false;
	if (!ft_strncmp(cmd->str, "~", 1))
	{
		free (cmd->str);
		cmd->str = ft_strdup(&search_in_env(utils, "HOME")[5]);
	}
	i = -1;
	while (cmd->str && cmd->str[++i])
	{
		if (cmd->str[i] == '$' && cmd->str[i + 1])
			var_handling(utils, &cmd->str, i);
		else if (cmd->str[i] == '\"')
			i += d_quote_handling(utils, cmd, i);
		else if (cmd->str[i] == '\'')
			i += quote_handling(cmd, '\'', i);
	}
	ft_putendl_fd(cmd->str, STDOUT_FILENO, flag);
	return (EXIT_SUCCESS);
}
