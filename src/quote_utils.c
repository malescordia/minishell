/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:35 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 15:09:12 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* skip quoted strings */
int	ignore_quotes(char *input, int i)
{
	char	quote;

	if (check_char(input[i]) == 3)
	{
		quote = input[i++];
		while (input[i] && input[i] != quote)
			i++;
		i++;
	}
	return (i);
}

/* returns string inside the quotes */
char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	quote;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), (ft_strlen(str) - get_nb_of_quotes(str) + 1));
	while (str[i])
	{
		if (check_char(str[i]) == 3)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				tmp[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			tmp[j++] = str[i++];
	}
	return (tmp);
}

/* returns the number of quotes */
int	get_nb_of_quotes(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (check_char(str[i] == 3))
		{
			i = ignore_quotes(str, i);
			n += 2;
		}
		else
			i++;
	}
	return (n);
}
