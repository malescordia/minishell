/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:57:34 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/04 15:59:41 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_error(t_data *data, char *filename, int child)
{
	perror(filename);
	if (filename)
		free(filename);
	if (child)
	{
		data->exit = 1;
		free_data(data);
	}
	else
		return (1);
	return (0);
}
