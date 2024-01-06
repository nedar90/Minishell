/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrajabia <nrajabia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:25:31 by nrajabia          #+#    #+#             */
/*   Updated: 2023/09/25 11:07:17 by nrajabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		num1;
	int		num2;

	if (!s1)
		return (NULL);
	str = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	num1 = 0;
	while (s1 && s1[num1])
	{
		str[num1] = s1[num1];
		num1++;
	}
	num2 = 0;
	while (s2[num2] != '\0')
		str[num1++] = s2[num2++];
	str[num1] = '\0';
	free(s1);
	return (str);
}
