/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_b_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:24:24 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 13:53:54 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_env(t_utils *utils, char *str)
{
	int		i;
	char	*path;

	i = 0;
	while (utils->env[i])
	{
		path = ft_strnstr(utils->env[i], str, ft_strlen(str));
		if (path)
			return (path);
		i++;
	}
	return (NULL);
}

/* char	**search_in_env(t_utils *utils, char *str)
{
	int	i;

	i = -1;
	while (utils->env[++i])
		if (!ft_strncmp(utils->env[i], str, ft_strlen(str)))
			return (&utils->env[i]);
	return (NULL);
} */

int	do_env(t_utils *utils, struct s_cmd *cmd)
{
	int		i;

	if (cmd->str)
	{
		print_err("env: `", cmd->str, "`: No such file or directory");
		return (EXIT_FAILURE);
	}
	i = -1;
	while (utils->env[++i])
	{
		if (cmd->builtins == do_export)
			ft_putendl_fd("declare -x ", STDOUT_FILENO, false);
		ft_putendl_fd(utils->env[i], STDOUT_FILENO, true);
	}
	return (EXIT_SUCCESS);
}
