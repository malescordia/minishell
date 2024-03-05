/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:49:00 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/07 15:24:41 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*sub;

	if (start >= ft_strlen(str))
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		sub[0] = 0;
	}
	else if (len >= (ft_strlen(str) - start))
		sub = ft_strdup(&str[start]);
	else
	{
		sub = malloc(sizeof(char) * (len + 1));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, &str[start], len + 1);
	}
	return (sub);
}
