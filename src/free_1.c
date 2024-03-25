/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:49:51 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/25 14:01:48 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (1);
	while (arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	return (0);
}

void	free_list(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

void	free_list_malloc(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp->content);
		free(tmp);
	}
	if (list)
		free(list);
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;
	t_cmds	*head;

	head = cmds;
	while (head)
	{
		tmp = head;
		head = head->next;
		free_array(tmp->args);
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	int	exit_status;

	if (!data)
		exit(data->exit);
	close(0);
	close(1);
	close(2);
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	if (data->input)
		free(data->input);
	if (data->main_input)
		free_array(data->main_input);
	if (data->cmds)
		free_cmds(data->cmds);
	free_list_malloc(data->env);
	free_list_malloc(data->export);
	exit_status = data->exit;
	free(data);
	rl_clear_history();
	exit (exit_status);
}
