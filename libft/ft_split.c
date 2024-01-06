/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzhan <kzhan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:06:47 by nrajabia          #+#    #+#             */
/*   Updated: 2023/08/23 14:11:48 by kzhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// flag = 0 partition's counter
static char	**ft_free_split(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	return (NULL);
}

static int	ft_splitlen(char *s, char c, int flag)
{
	int	count;
	int	part;
	int	i;

	part = 1;
	count = 1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			part++;
			while (s[i] != c && s[i] != '\0')
			{
				count++;
				i++;
			}
			if (flag)
				return (count);
		}
		else
			i++;
	}
	return (part);
}

static int	fill_word(char *s, char c, char **array, int j)
{
	int	i;
	int	len;

	i = -1;
	len = ft_splitlen(s, c, 1);
	array[j] = malloc(len * sizeof(char));
	if (!array[j])
		ft_free_split(array, j);
	while (++i < len)
		array[j][i] = s[i];
	array[j][i -1] = '\0';
	return (len -1);
}

char	**ft_split(char *s, char c)
{
	char	**array;
	int		len;
	int		j;
	int		i;

	j = -1;
	len = ft_splitlen(s, c, 0);
	array = malloc (len * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (++j < len -1)
	{
		while (s[i] == c)
			i++;
		i += fill_word(&s[i], c, array, j);
	}
	array[j] = 0;
	return (array);
}
