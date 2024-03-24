/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 16:24:32 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/24 22:00:51 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reset_fds(t_data *data)
{
	dup2(data->fd_out, STDOUT_FILENO);
	close(data->fd_out);
	dup2(data->fd_in, STDIN_FILENO);
	close(data->fd_in);
}

int	redir_in(t_data *data, char *in_file, int heredoc, int child)
{
	int		file_fd;
	char	*clean_file;

	clean_file = remove_quotes(in_file);
	file_fd = open(clean_file, O_RDONLY);
	if (file_fd < 0)
		return (open_error(data, clean_file, child));
	else
	{
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
		if (heredoc)
			unlink(clean_file);
	}
	free(clean_file);
	return (0);
}

int	redir_out(t_data *data, char *out_file, int append, int child)
{
	int		file_fd;
	char	*clean_file;

	clean_file = remove_quotes(out_file);
	if (!append)
		file_fd = open(clean_file, O_CREAT | O_RDWR | O_TRUNC, 0664);
	else
		file_fd = open(clean_file, O_CREAT | O_RDWR | O_APPEND, 0664);
	if (file_fd < 0)
		return (open_error(data, clean_file, child));
	else
	{
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
	}
	free(clean_file);
	return (0);
}

int	redir_set(t_data *data, char **main_input, int position, int child)
{
	int	i;
	int	error;

	i = position;
	error = 0;
	while (main_input[i] && main_input[i][0] && ft_strcmp(main_input[\
		i], "|") != 0)
	{
		if (ft_strcmp(main_input[i], "<") == 0)
			error = redir_in(data, main_input[i + 1], 0, child);
		else if (ft_strcmp(main_input[i], "<<") == 0)
			error = redir_in(data, main_input[i + 1], 1, child);
		else if (ft_strcmp(main_input[i], ">") == 0)
			error = redir_out(data, main_input[i + 1], 0, child);
		else if (ft_strcmp(main_input[i], ">>") == 0)
			error = redir_out(data, main_input[i + 1], 1, child);
		i++;
		if (error)
			return (1);
	}
	return (0);
}
