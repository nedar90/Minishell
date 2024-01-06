/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:36:35 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/12 17:12:41 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd, bool flag)
{
	int	i;

	i = 0;
	if (s && *s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
	if (flag)
		write(fd, "\n", 1);
}
