/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:43:03 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/07 15:24:34 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	str = (char *)big;
	if (little[0] == 0)
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while ((i + j) < len && (str[i + j] == little[j]))
		{
			if (little[j + 1] == 0)
				return (&str[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
