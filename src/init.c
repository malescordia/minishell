/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:26:46 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/05 14:00:01 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// var_init
int	init_data(t_data *data)
{
	char	**tmp;

	data->cmd_in_fd = 0;
	data->fd_in = dup(0);
	data->fd_out = dup(1);
	data->main_input = split_input(data->input);
	tmp = expander(data);
	free_array(data->main_input);
	data->main_input = input_dup(tmp);
	free_array(tmp);
	data->nb_of_cmds = get_cmds_nb(data->main_input);
	data->cmds = init_cmds(data);
	return (0);
}

// cmd_list_init
t_cmds	*init_cmds(t_data *data)
{
	int		i;
	int		count;
	t_cmds	*current;
	t_cmds	*cmds;

	i = 0;
	count = 0;
	if (data->nb_of_cmds <= 0)
		return (NULL);
	cmds = NULL;
	while (count < data->nb_of_cmds)
	{
		current = create_node(data, i);
		while (data->main_input[i] && ft_strcmp(data->main_input[i], "|") != 0)
			i++;
		if (data->main_input[i] && ft_strcmp(data->main_input[i], "|") == 0)
			i++;
		ft_lstadd_back((t_list **)&cmds, (t_list *)current);
		count++;
	}
	return (cmds);
}
