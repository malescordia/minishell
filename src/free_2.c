/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:27:44 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 14:01:52 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_heredoc(t_data *data)
{
	int	exit_status;

	close(0);
	close(1);
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	if (data->input)
		free(data->input);
	if (data->main_input)
		free_array(data->main_input);
	free_list_malloc(data->env);
	free_list_malloc(data->export);
	exit_status = data->exit;
	free(data);
	rl_clear_history();
	exit (exit_status);
}
