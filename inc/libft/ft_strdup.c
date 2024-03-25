/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 13:35:03 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 13:43:11 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*buff;

	if (!str)
		return (NULL);
	buff = (char *) malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!buff)
		return (NULL);
	ft_strlcpy(buff, str, ft_strlen(str) + 1);
	return (buff);
}
