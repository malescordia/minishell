/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfront_trim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:15:11 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 13:32:57 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfront_trim(char *str, char *trim)
{
	int		i;
	int		j;
	char	*buf;

	j = 0;
	while (str[j] && ft_strchr(trim, str[j]))
		j++;
	i = ft_strlen(str) - j;
	buf = ft_calloc(sizeof(char), (i + 1));
	if (!buf)
		return (0);
	i = 0;
	while (str[j])
		buf[i++] = str[j++];
	return (buf);
}
