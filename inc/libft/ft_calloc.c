/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:53:05 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/07 15:29:13 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t len)
{
	void	*ptr;

	if (n == 0)
		ptr = NULL;
	ptr = malloc(n * len);
	if (ptr == NULL)
	{
		free(ptr);
		return (NULL);
	}
	ft_bzero(ptr, n * len);
	return (ptr);
}
