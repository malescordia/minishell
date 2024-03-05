/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:46:13 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/07 15:34:31 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)str;
	i = ft_strlen(ptr) - 1;
	if (c == 0)
		return (&ptr[i + 1]);
	while (i >= 0)
	{
		if (ptr[i] == c)
			return (&ptr[i]);
		i--;
	}
	return (NULL);
}
