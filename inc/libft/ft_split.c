/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:35:43 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/07 15:32:03 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(const char *str, char c)
{
	size_t	i;
	int		len;

	len = 0;
	i = 0;
	if (str[0] != c)
	{
		len++;
		i++;
	}
	while (i < ft_strlen(str))
	{
		if (str[i] != c && str[i - 1] == c)
			len++;
		i++;
	}
	return (len);
}

char	**get_words(char **arr, const char *str, char c, int len)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (j < len && str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c)
		{
			start = i;
			while (str[i] != c && str[i] != 0)
				i++;
			arr[j] = ft_substr(str, start, i - start);
			j++;
		}
	}
	return (arr);
}

char	**ft_split(const char *str, char c)
{
	char	**arr;
	int		len;

	if (!str[0])
	{
		arr = malloc(sizeof(char *));
		if (!arr)
		{
			free(arr);
			return (NULL);
		}
		arr[0] = 0;
		return (arr);
	}
	len = get_len(str, c);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
	{
		free(arr);
		return (NULL);
	}
	arr[len] = NULL;
	get_words(arr, str, c, len);
	return (arr);
}
