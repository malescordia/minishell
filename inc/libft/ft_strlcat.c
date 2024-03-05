/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:43:24 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/07 15:33:44 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (len == 0)
		return (src_len);
	if (len < dst_len)
		return (src_len + len);
	while (src[i] && dst_len < len - 1)
		dst[dst_len++] = src[i++];
	dst[dst_len] = 0;
	return ((dst_len - i) + src_len);
}
