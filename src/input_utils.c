/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:03:02 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 20:54:46 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	input_size(char **input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i])
		i++;
	return (i);
}

char	**input_dup(t_data *data, char **old)
{
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (input_size(old) + 1));
	if (!new)
		malloc_error(data);
	while (old && old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

/* returns 1 if white space */
/* returns 2 if operator */
/* returns 3 if quote */
/* returns 4 if dollar sign */
int	check_char(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '>' || c == '<' || c == '|')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	if (c == '$')
		return (4);
	return (0);
}
