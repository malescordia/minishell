/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:26:46 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 16:44:29 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_data(t_data *data)
{
	char	**new_input;

	data->cmd_in_fd = 0;
	data->fd_in = dup(STDIN_FILENO);
	data->fd_out = dup(STDOUT_FILENO);
	data->main_input = split_input(data, data->input);
	if (heredoc_init(data, data->main_input))
		return (1);
	new_input = expander(data);
	free_array(data->main_input);
	data->main_input = input_dup(data, new_input);
	free_array(new_input);
	data->nb_of_cmds = get_nb_of_cmds(data->main_input);
	data->cmds = init_cmds(data);
	sig_init();
	return (0);
}

/* creates the cmds list */
t_cmds	*init_cmds(t_data *data)
{
	int			i;
	int			n;
	t_cmds		*current;
	t_cmds		*cmds;

	i = 0;
	n = 0;
	if (data->nb_of_cmds <= 0)
		return (NULL);
	cmds = NULL;
	while (n < data->nb_of_cmds)
	{
		current = create_node(data, i);
		while (data->main_input[i] && ft_strcmp(data->main_input[i], "|") != 0)
			i++;
		if (data->main_input[i] && ft_strcmp(data->main_input[i], "|") == 0)
			i++;
		ft_lstadd_back((t_list **)&cmds, (t_list *)current);
		n++;
	}
	return (cmds);
}
