/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:40:58 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/27 17:33:01 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_signal = 0;

int	print_token_message(char token)
{
	ft_putstr_fd("error: unexpected token '", 2);
	write(2, &token, 1);
	ft_putstr_fd("\'\n", 2);
	return (1);
}

void	free_all(t_data *data, int ac, char **av)
{
	post_process_signal();
	signal_exit(data);
	free(data->input);
	free_array(data->main_input);
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
	(void)ac;
	(void)av;
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		malloc_error(data);
	data->env = init_env(envp);
	data->export = init_export(data);
	data->exit = 0;
	while (42)
	{
		sig_init();
		data->input = readline(PURPLE "Minishell> " R);
		if (ft_strlen(data->input) != 0)
			add_history(data->input);
		if (data->input && check_input(data))
			continue ;
		if (!init_data(data))
		{
			start_protocol(data);
			free_cmds(data->cmds);
		}
		free_all(data, ac, av);
	}
	exit(data->exit);
}
