/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_nochr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:16:17 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 13:34:03 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* compares s1 and s2 until s2 reaches c, excluding c */
int	ft_strcmp_nochr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < ft_strlen_chr(s2, c) - 1)
		i++;
	if (i < (int)ft_strlen(s1) - 1)
		return (1);
	return (s1[i] - s2[i]);
}
