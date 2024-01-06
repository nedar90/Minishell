/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_cmd_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:32:32 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/30 10:42:43 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_executer(t_utils *utils, char **cmd)
{
	int		i;
	char	**path;
	char	*path_cmd;

	if (!access(cmd[0], F_OK | X_OK))
		execve(cmd[0], cmd, utils->env);
	path_cmd = search_in_env(utils, "PATH");
	if (path_cmd)
	{
		path = ft_split(&path_cmd[5], ':');
		i = -1;
		while (path[++i])
		{
			path_cmd = ft_strjoin(path[i], "/");
			path_cmd = ft_strjoin(path_cmd, cmd[0]);
			if (!access(path_cmd, F_OK | X_OK))
				execve(path_cmd, cmd, utils->env);
			free(path_cmd);
		}
		free(path);
		ft_free(cmd);
	}
	return (127);
}
