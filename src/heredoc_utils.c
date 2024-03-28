/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:37:52 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/28 14:24:17 by gude-cas         ###   ########.fr       */
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

/* modifies the terminal settings to disable the quit character 
   allows us to input multiple lines */
void	change_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/* generates tmp file based on the number of here_docs 
   increments 'x' according to the number of here_docs */
char	*filename_init(int nb_of_heredocs)
{
	int		i;
	char	*buffer;
	char	*filename;

	i = 0;
	buffer = NULL;
	filename = ft_strdup("/tmp/tmpxxx");
	while (i < nb_of_heredocs)
	{
		buffer = ft_strdup(filename);
		free(filename);
		filename = ft_strjoin(buffer, "x");
		free(buffer);
		i++;
	}
	return (filename);
}

/* opens the file and returns its fd */
int	create_file(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd < 0)
		open_error(data, filename, 1);
	free(filename);
	return (fd);
}
