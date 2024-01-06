/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ft_error2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:49:56 by kzhan             #+#    #+#             */
/*   Updated: 2023/09/30 10:24:38 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg_err(char *arg)
{
	char	*str;

	str = ft_strtrim(arg, " ");
	if (((!ft_strncmp(str, ">>", 2)
				|| !ft_strncmp(str, "<<", 2)) && !str[2])
		|| ((!ft_strncmp(str, ">", 1)
				|| !ft_strncmp(str, "<", 1)) && !str[1]))
	{
		print_err(TOKEN_ERR, str, "\'");
		free(str);
		return (1);
	}
	else if (!ft_strncmp(str, "$", 1) && !str[1])
	{
		free(str);
		ft_error("$: command not found\n", true);
		return (1);
	}
	free(str);
	return (0);
}
