/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_b_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:30:43 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/26 08:31:14 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_isalpha(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '=')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z')
			&& !(str[i] >= 'A' && str[i] <= 'Z')
			&& !(str[i] == '_'))
			return (1);
	}
	return (0);
}

int	check_cmd_str(t_utils *utils, t_cmd *cmd)
{
	if (!cmd->str)
		return (do_env(utils, cmd));
	if (ft_isalpha(cmd->str))
	{
		print_err("export: `", cmd->str, "`: not a valid identifier");
		reset(utils);
	}
	return (1);
}

int	update_env(t_utils *utils, char *str, int size, int end)
{
	int	i;

	i = -1;
	while (utils->env[++i])
		if (!ft_strncmp(utils->env[i], str, size))
			break ;
	if (!utils->env[i])
		return (0);
	free(utils->env[i]);
	utils->env[i] = ft_substr(str, 0, end);
	return (1);
}

int	append_env(t_utils *utils, char **old_env, int end)
{
	int		i;
	char	**new_env;

	i = 0;
	while (old_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (-1);
	new_env[i++] = NULL;
	new_env[--i] = ft_substr(utils->cmds->str, 0, end);
	while (--i > -1)
		new_env[i] = ft_strdup(old_env[i]);
	ft_free(utils->env);
	utils->env = new_env;
	return (0);
}

int	do_export(t_utils *utils, struct s_cmd *cmd)
{
	int		len;
	int		i;
	bool	flag;

	len = 0;
	i = -1;
	flag = true;
	if (!check_cmd_str(utils, cmd))
		return (0);
	while (cmd->str[++i])
	{
		if (cmd->str[i] == ' ')
			break ;
		if (flag)
			len++;
		if (cmd->str[i] == '=')
			flag = false;
	}
	if (flag)
		return (0);
	if (!update_env(utils, cmd->str, len++, i))
		append_env(utils, utils->env, i);
	return (EXIT_SUCCESS);
}
