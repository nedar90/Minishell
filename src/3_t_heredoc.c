/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_t_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:38:41 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/30 14:42:27 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	open_heredoc(void)
{
	int	fd;

	fd = open("heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (!fd)
		return (EXIT_FAILURE);
	return (fd);
}

int	heredoc(t_utils *utils, t_cmd *cmd)
{
	char	*line;
	int		fd;

	if (!cmd->heredoc_eof)
		return (0);
	fd = open_heredoc();
	signal(SIGINT, sigint_heredoc);
	line = readline("> ");
	while (ft_strncmp(line, cmd->heredoc_eof, ft_strlen(cmd->heredoc_eof)))
	{
		if (!line)
		{
			ft_putendl_fd(EOF_ERR, STDOUT_FILENO, false);
			break ;
		}
		if (g_exitnbr == 130)
			return (g_exitnbr);
		if (is_dollar(line) != -1)
			var_handling(utils, &line, is_dollar(line));
		ft_putendl_fd(line, fd, true);
		free (line);
		line = readline("> ");
	}
	close (fd);
	return (EXIT_SUCCESS);
}
