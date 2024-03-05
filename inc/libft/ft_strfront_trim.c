/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfront_trim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:15:11 by gude-cas          #+#    #+#             */
/*   Updated: 2024/02/22 14:53:19 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfront_trim(char *str, char *trim)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] && ft_strchr(trim, str[i]))
		i++;
	j = ft_strlen(str) - j;
	tmp = ft_calloc(sizeof(char), (j + 1));
	if (!tmp)
		return (0);
	j = 0;
	while (str[i])
		tmp[j++] = str[i++];
	return (tmp);
}
