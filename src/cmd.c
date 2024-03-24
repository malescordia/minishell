/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:02:57 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 21:55:50 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_next_cmd(char **input, int i)
{
	while (input[i] && input[i][0] && ft_strcmp(input[i], "|") \
		!= 0)
		i++;
	if (input[i] && input[i][0] && ft_strcmp(input[i], "|") == 0)
		i++;
	return (i);
}

/* returns how many valid cmds there are in main_input */
int	get_nb_of_cmds(char **input)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (input[i])
	{
		n++;
		while (input[i] && ft_strcmp(input[i], "|") != 0)
			i++;
		if (input[i] && ft_strcmp(input[i], "|") == 0)
			i++;
	}
	return (n);
}

int	get_nb_of_args(char **input, int i)
{
	int	j;
	int	count;

	j = i;
	count = 0;
	while (input[j] && !input[j][0])
		j++;
	while (input[j])
	{
		if (ft_strcmp(input[j], ">") == 0 || ft_strcmp(input[j], ">>") == 0
			|| ft_strcmp(input[j], "<") == 0 || ft_strcmp(input[j], "<<") == 0)
			j += 2;
		else if (ft_strcmp(input[j], "|") == 0)
			break ;
		else
		{
			count += count_words(input[j]);
			j++;
		}
	}
	return (count);
}

t_cmds	*create_node(t_data *data, int i)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		malloc_error(data);
	cmds->args = tokenizer(data, data->main_input, i);
	cmds->next = NULL;
	return (cmds);
}
