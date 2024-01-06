/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_b_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:02:41 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/26 08:22:24 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	clean_env(t_utils *utils, char *str)
{
	int	i;

	i = -1;
	while (utils->env[++i])
	{
		if (!ft_strncmp(utils->env[i], str, ft_strlen(str)))
			return (i);
	}
	return (-1);
}

int	do_unset(t_utils *utils, struct s_cmd *cmd)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = ft_split(cmd->str, ' ');
	j = -1;
	while (tmp[++j])
	{
		i = clean_env(utils, tmp[j]);
		if (i == -1)
			continue ;
		while (utils->env[i])
		{
			utils->env[i] = utils->env[i + 1];
			i++;
		}
		free(utils->env[i]);
	}
	return (EXIT_SUCCESS);
}
