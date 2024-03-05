/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:02:57 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/05 13:25:50 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// find_cmd_pos
int	find_next_cmd(char **input, int i)
{
	while (input[i] && input[i][0] && ft_strcmp(input[i], "|") != 0)
		i++;
	if (input[i] && input[i][0] && ft_strcmp(input[i], "|") == 0)
		i++;
	return (i);
}

int	get_cmds_nb(char **input)
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

int	get_args_nb(char **input, int i)
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

// cmdlist_lstnew
t_cmds	*create_node(t_data *data, int i)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		perror("malloc");
	cmds->args = tokenizer(data->main_input, i);
	cmds->next = NULL;
	return (cmds);
}
