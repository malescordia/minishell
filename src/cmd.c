/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:02:57 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 15:29:40 by gude-cas         ###   ########.fr       */
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

/* returns the amount of args the specified cmd has,
   it stops once if finds a pipe */
int	get_nb_of_args(char **input, int i)
{
	int	count;

	count = 0;
	while (input[i] && !input[i][0])
		i++;
	while (input[i])
	{
		if (ft_strcmp(input[i], ">") == 0 || ft_strcmp(input[i], ">>") == 0
			|| ft_strcmp(input[i], "<") == 0 || ft_strcmp(input[i], "<<") == 0)
			i += 2;
		else if (ft_strcmp(input[i], "|") == 0)
			break ;
		else
		{
			count += count_words(input[i]);
			i++;
		}
	}
	return (count);
}

/* much like ft_lstnew but for cmds list */
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
