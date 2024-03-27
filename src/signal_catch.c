/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_catch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:22:19 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/27 12:11:03 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_stop(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_setup(int signum)
{
	if (signum == SIGQUIT)
		g_signal = SIGQUIT;
	if (signum == SIGINT)
		g_signal = SIGINT;
	if (signum == SIGPIPE)
		g_signal = SIGPIPE;
}

void	signal_exit(t_data *data)
{
	if (!(data->input))
	{
		write(STDOUT_FILENO, "\n", 1);
		free_data(data);
	}
}

/* CTRL-C sends an interrupt signal */
/* CTRL-\ sends a quit signal */
void	sig_init(void)
{
	signal(SIGINT, signal_stop);
	signal(SIGQUIT, SIG_IGN);
}

void	post_process_signal(void)
{
	if (!g_signal)
		return ;
	if (g_signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	if (g_signal == SIGINT)
		printf("\n");
	g_signal = 0;
}
