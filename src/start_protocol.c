/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:15:24 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/27 17:31:45 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	start_protocol(t_data *data)
{
	int		i;
	int		fork_id;
	int		pipe_fd[2];
	int		done_cmds;

	i = 0;
	done_cmds = 0;
	if (!data->cmds)
		return ;
	signal(SIGQUIT, sig_setup);
	while (done_cmds < data->nb_of_cmds)
	{
		if (pipe(pipe_fd) < 0)
			pipe_error(data, pipe_fd);
		fork_id = fork();
		if (fork_id < 0)
			fork_error(data, pipe_fd);
		if (fork_id == 0)
			child_exec(data, pipe_fd, done_cmds, i);
		else
			parent_exec(data, pipe_fd, done_cmds, i);
		i = find_next_cmd(data->main_input, i);
		done_cmds++;
	}
	get_exit_status(data, fork_id, done_cmds);
}

void	child_exec(t_data *data, int *pipe_fd, int done_cmds, int position)
{
	int			i;
	t_cmds		*cmds;

	cmds = data->cmds;
	i = done_cmds;
	signal(SIGPIPE, sig_setup);
	while (i > 0)
	{
		cmds = cmds->next;
		i--;
	}
	if (done_cmds != 0)
	{
		dup2(data->cmd_in_fd, STDIN_FILENO);
		close(data->cmd_in_fd);
	}
	if (done_cmds < data->nb_of_cmds - 1)
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (data->nb_of_cmds == 1 && is_builtin(cmds->args[0]))
		free_data(data);
	redir_set(data, data->main_input, position, 1);
	execute(data, cmds->args);
}

void	parent_exec(t_data *data, int *pipe_fd, int done_cmds, int position)
{
	int			i;
	t_cmds		*cmds;

	i = done_cmds;
	cmds = data->cmds;
	while (i-- > 0)
		cmds = cmds->next;
	if (data->nb_of_cmds == 1)
	{
		if (is_builtin(cmds->args[0]) && redir_set(data, data->main_input, \
			position, 0) == 0)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			read_builtin(data, cmds->args, 1);
		}
	}
	if (done_cmds > 0)
		close(data->cmd_in_fd);
	if (done_cmds < data->nb_of_cmds - 1)
		data->cmd_in_fd = pipe_fd[0];
	else
		close(pipe_fd[0]);
	close(pipe_fd[1]);
	signal(SIGINT, sig_setup);
}

void	get_exit_status(t_data *data, int fork_id, int done_cmds)
{
	int	status;

	if (data->nb_of_cmds == 1 && is_builtin(data->cmds->args[0]) \
		== 1)
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
		if (fork_id != -1 && WIFSIGNALED(status))
			g_signal = WTERMSIG(status);
		else
			g_signal = 0;
		done_cmds--;
	}
	reset_fds(data);
}
