/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_b_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:40:35 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 14:22:40 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update(t_utils *utils, char *str, char *path)
{
	int		i;
	char	*tmp;

	i = -1;
	while (utils->env[++i])
	{
		if (!ft_strncmp(utils->env[i], str, ft_strlen(str)))
		{
			tmp = ft_strjoin(ft_strdup(str), path);
			free(utils->env[i]);
			utils->env[i] = tmp;
		}
	}
	free(path);
}

int	do_cd(t_utils *utils, struct s_cmd *cmd)
{
	int		ret;
	char	*path;
	char	*old;

	old = getcwd(NULL, 0);
	if (argument_err(cmd))
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd->str, "-", 1))
		ret = chdir(&search_in_env(utils, "OLDPWD")[7]);
	else if (!ft_strncmp(cmd->str, "~/Desktop", 9))
	{
		if (search_in_env(utils, "HOME"))
			path = ft_strjoin(ft_strdup(&search_in_env(utils, "HOME")[5]), \
			"/Desktop");
		ret = chdir(path);
	}
	else if (!cmd->str || !ft_strncmp(cmd->str, "~", 1))
		ret = chdir(&search_in_env(utils, "HOME")[5]);
	else
		ret = chdir(cmd->str);
	if (ret != 0)
		minishell_err(utils, "cd", false);
	update(utils, "PWD=", getcwd(NULL, 0));
	update(utils, "OLDPWD=", old);
	return (EXIT_SUCCESS);
}
