/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 12:13:28 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 14:15:43 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intsize(int x)
{
	size_t	count;

	count = 0;
	if (x <= 0)
		count++;
	while (x)
	{
		x = x / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*s;
	long int	nb;
	int			i;

	nb = (long)n;
	i = ft_intsize(nb);
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (0);
	s[i] = '\0';
	if (nb == 0)
		s[0] = '0';
	if (nb < 0)
	{
		s[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		s[--i] = '0' + (nb % 10);
		nb = nb / 10;
	}
	return (s);
}
