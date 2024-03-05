/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:15:24 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/05 14:14:55 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// run
void	start(t_data *data)
{
	int	pipe_fd[2];
	int	fork_id;
	int	done_cmds;
	int	i;

	done_cmds = 0;
	i = 0;
	if (!data->cmds)
		return ;
	while (done_cmds < data->nb_of_cmds)
	{
		if (pipe(pipe_fd) < 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			perror("pipe");
			data->exit = 1;
			free_data(data);
		}
		fork_id = fork();
		if (fork_id < 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			perror("fork");
			data->exit = 1;
			free_data(data);
		}
		if (fork_id == 0)
		{
			child_exec(data, pipe_fd, done_cmds, i);
		}
		else
		{
			parent_exec(data, pipe_fd, done_cmds, i);
		}
		i = find_next_cmd(data->main_input, i);
		done_cmds++;
	}
	get_exit_status(data, fork_id, done_cmds);
}

// child
void	child_exec(t_data *data, int *pipe_fd, int done_cmds, int position)
{
	int		i;
	t_cmds	*cmds;

	i = done_cmds;
	cmds = data->cmds;
	while (i > 0)
	{
		cmds = cmds->next; // iterate until find the next command to execute
		i--;
	}
	if (done_cmds != 0) // if there are commands and its not the first one
	{
		dup2(data->cmd_in_fd, 0); // get input from previous
		close(data->cmd_in_fd);
	}
	if (done_cmds < data->nb_of_cmds - 1)
		dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (data->nb_of_cmds == 1 && is_builtin(cmds->args[0]))
		free_data(data);
	redir_set(data, data->main_input, position, 1);
	execute(data, cmds->args);
}

// parent
void	parent_exec(t_data *data, int *pipe_fd, int done_cmds, int position)
{
	int		i;
	t_cmds	*cmds;

	i = done_cmds;
	cmds = data->cmds;
	while (i-- > 0)
		cmds = cmds->next;
	if (data->nb_of_cmds == 1)
	{
		if (is_builtin(cmds->args[0]) && redir_set(data, data->main_input,
				position, 0) == 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			read_builtin(data, cmds->args, 1);
		}
		if (done_cmds > 0)
			close(data->cmd_in_fd);
		if (done_cmds < data->nb_of_cmds - 1)
			data->cmd_in_fd = pipe_fd[0];
		else
			close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

void	get_exit_status(t_data *data, int fork_id, int done_cmds)
{
	int	status;

	if (data->nb_of_cmds == 1 && is_builtin(data->cmds->args[0]) == 1)
	{
		wait(&status);
		reset_fds(data);
		return ;
	}
	while (done_cmds > 0)
	{
		wait(&status);
		if (fork_id != -1 && WIFEXITED(status))
			data->exit = WEXITSTATUS(status);
		done_cmds--;
	}
	reset_fds(data);
}
