/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:35:43 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 14:15:33 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	splitcount(char const *s, char c)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char	*splitmake(const char *s, char c)
{
	char	*buff;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	buff = (char *) malloc (sizeof(char) * (i + 1));
	if (!buff)
		return (NULL);
	ft_strlcpy(buff, s, i + 1);
	return (buff);
}

void	*splitfree(char **buff, int n)
{
	while (n > 0)
		free (buff[--n]);
	free (buff);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**buff;
	char	*content;
	int		i;
	int		n;

	buff = (char **)malloc(sizeof(char *) * splitcount(str, c));
	if (!buff)
		return (NULL);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			content = splitmake(str + i, c);
			if (!content)
				return (splitfree(buff, n));
			buff[n++] = content;
			while (str[i + 1] && str[i + 1] != c)
				i++;
		}
		i++;
	}
	buff[n] = NULL;
	return (buff);
}
