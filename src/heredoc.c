/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:31:08 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/24 15:35:49 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_heredoc(t_data *data, char *limiter, int here_num)
{
	char	*filename;
	int		pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	filename = filename_init(here_num);
	pid = fork();
	if (pid < 0)
		fork_error(data, NULL);
	if (pid == 0)
	{
		signal(SIGINT, signal_heredoc);
		child_heredoc(data, filename, limiter);
	}
	else
	{
		wait(&status);
		if (pid != -1 && WIFEXITED(status) && WEXITSTATUS(status) == (128 + \
			SIGINT))
		{
			g_signal = SIGINT;
			unlink(filename);
		}
	}
	return (filename);
}

int	heredoc_init(t_data *data, char **input)
{
	int		i;
	char	*buffer;

	i = 0;
	if (!input || !input[0] || !input[0][0])
		return (0);
	while (input[i])
	{
		if (ft_strcmp(input[i], "<<") == 0)
		{
			buffer = read_heredoc(data, input[i + 1], i);
			free(input[i + 1]);
			input[i + 1] = ft_strdup(buffer);
			free(buffer);
			if (g_signal == SIGINT)
			{
				g_signal = 0;
				return (1);
			}
			i += 2;
		}
		else
			i++;
	}
	return (0);
}

void	child_heredoc(t_data *data, char *filename, char *limiter)
{
	int		fd;
	char	*output;
	char	*line;

	line = NULL;
	fd = create_file(data, filename);
	while (1)
	{
		change_terminal();
		line = readline("> ");
		if (g_signal == SIGINT)
			data->exit = 128 + SIGINT;
		else if (!line)
			heredoc_eof(limiter);
		output = output_heredoc(data, limiter, line);
		if (!output)
			break ;
		free(line);
		ft_putendl_fd(output, fd);
		free(output);
	}
	if (line)
		free(line);
	close(fd);
	free_heredoc(data);
}

char	*output_heredoc(t_data *data, char *limiter, char *line)
{
	char	*buffer;

	buffer = remove_quotes(limiter);
	if (g_signal == SIGINT || !line || ft_strcmp_nochr(buffer, line, '\n') == 0)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	if (!ft_strchr(limiter, '\'') && !ft_strchr(limiter, '\"'))
		buffer = get_value(data, line);
	else
		buffer = ft_strdup(line);
	return (buffer);
}
