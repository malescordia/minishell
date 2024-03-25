/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:13:32 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 13:35:43 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* compares s1 and s2 until s2 reaches c, including c */
int	ft_strcmp_chr(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i] && i < ft_strlen_chr(s2, c)))
		i++;
	return (s1[i] - s2[i]);
}
