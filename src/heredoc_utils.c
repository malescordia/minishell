/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:37:52 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/24 15:34:45 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		printf("\n");
		close(STDIN_FILENO);
	}
}

void	change_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char	*filename_init(int here_num)
{
	int		i;
	char	*buffer;
	char	*filename;

	i = 0;
	buffer = NULL;
	filename = ft_strdup("/tmp/tmpxxx");
	while (i < here_num)
	{
		buffer = ft_strdup(filename);
		free(filename);
		filename = ft_strjoin(buffer, "x");
		free(buffer);
		i++;
	}
	return (filename);
}

int	create_file(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_error(data, filename, 1);
	free(filename);
	return (fd);
}
