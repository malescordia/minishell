/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:08:07 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 13:31:21 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *trim)
{
	int		i;
	char	*buffer;

	while (*str && ft_strchr(trim, *str))
		str++;
	i = ft_strlen(str) - 1;
	while (i > 0 && ft_strchr(trim, str[i]))
		i--;
	i++;
	buffer = (char *)malloc(sizeof(char) * (i + 1));
	if (!buffer)
		return (0);
	ft_strlcpy(buffer, str, i + 1);
	return (buffer);
}
