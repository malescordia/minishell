/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:43:27 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 22:12:24 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	list_print(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		ft_putendl_fd((char *)tmp->content, 1);
		tmp = tmp->next;
	}
}
