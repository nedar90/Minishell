/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:37:10 by kzhan             #+#    #+#             */
/*   Updated: 2023/09/25 14:10:32 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_len(char const *s, unsigned int start, size_t len)
{
	if (ft_strlen(s) < len + start)
		return ((ft_strlen(s) - start));
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			ni;
	char			*str;

	i = 0;
	ni = 0;
	len = check_len(s, start, len);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i] != '\0' && s[i])
	{
		if (i >= start && ni < len)
			str[ni++] = s[i];
		i++;
	}
	str[ni] = '\0';
	return (str);
}
