/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_expander.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:41:24 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 14:15:52 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len(char **str, int start)
{
	int		len;

	len = 1;
	while (ft_isalnum((*str)[len + start]))
		len++;
	return (len);
}

char	*find_env(t_utils *utils, char **str, int *size, int start)
{
	char	*sub_str;
	int		len;
	int		j;

	j = -1;
	len = get_len(str, start);
	while (utils->env[++j])
		if (!ft_strncmp(utils->env[j], &(*str)[start + 1], len - 1))
			break ;
	if (utils->env[j])
	{
		*size = ft_strlen(&utils->env[j][len]);
		sub_str = ft_strjoin(ft_substr((*str), 0, start), &utils->env[j][len]);
	}
	else
		sub_str = ft_strjoin(ft_substr((*str), 0, start), "");
	return (sub_str);
}

char	*check_q_mark(char **str, int *size, int start)
{
	char	*sub_str;
	char	*num;

	if ((*str)[start + 1] == '?')
	{
		num = ft_itoa(g_exitnbr);
		*size = ft_strlen(num);
		sub_str = ft_strjoin(ft_substr((*str), 0, start), num);
		free (num);
		return (sub_str);
	}
	return (NULL);
}

int	var_handling(t_utils *utils, char **str, int start)
{
	char	*sub_str;
	int		size;
	int		len;

	size = 0;
	sub_str = check_q_mark(str, &size, start);
	if (!sub_str)
	{
		len = get_len(str, start);
		sub_str = find_env(utils, str, &size, start);
	}
	else
		len = 2;
	if ((*str)[len + start])
		sub_str = ft_strjoin(sub_str, &(*str)[len + start]);
	free((*str));
	(*str) = sub_str;
	return (size);
}
