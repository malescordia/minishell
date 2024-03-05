/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:48:38 by gude-cas          #+#    #+#             */
/*   Updated: 2024/02/22 14:50:32 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int len)
{
	char	*result;

	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	return (result);
}
