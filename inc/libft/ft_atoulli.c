/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoulli.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:16:54 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 19:17:05 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long int	ft_atoulli(const char *str)
{
	unsigned long long	n;
	unsigned long long	i;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else if (str[i] == '-' || str[i] == '+')
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
		{
			n = (n * 10) + (str[i] - '0');
			i++;
		}
	}
	return (n);
}
