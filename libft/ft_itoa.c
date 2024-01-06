/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 11:47:52 by nrajabia          #+#    #+#             */
/*   Updated: 2022/12/18 11:48:08 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	condition(int flag, int true_con, int false_con)
{
	if (flag)
	{
		return (true_con);
	}
	return (false_con);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	str_size;
	int		n_mem;

	n_mem = n;
	str_size = condition((n < 0), 3, 2);
	while ((n > 9 || n < -9) && str_size++)
		n /= 10;
	str = (char *)malloc((str_size--) * sizeof(char));
	if (!str)
		return (NULL);
	str[str_size--] = '\0';
	while (n_mem > 9 || n_mem < -9)
	{
		str[str_size--] = \
		condition((n_mem < 0), -(n_mem % 10), n_mem % 10) + '0';
		n_mem = n_mem / 10;
	}
	str[0] = condition((n_mem < 0), '-', (n_mem + '0'));
	str[1] = condition((n_mem < 0), (-n_mem + '0'), str[1]);
	return (str);
}
