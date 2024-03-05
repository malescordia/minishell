/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:50:35 by gude-cas          #+#    #+#             */
/*   Updated: 2024/02/22 17:14:47 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// skip_quotes
int	ignore_quotes(char *input, int i)
{
	char	quote;

	if (input[i] == '\'' || input[i] == '\"')
	{
		quote = input[i++];
		while (input[i] && input[i] != quote)
			i++;
		i++;
	}
	return (i);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*tmp;
	char	quote;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), (ft_strlen(str) - get_quote_nb(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
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

// quote_num
int	get_quote_nb(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = ignore_quotes(str, i);
			n += 2;
		}
		else
			i++;
	}
	return (n);
}
