/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:40:58 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/05 14:02:48 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* PATH_MAX IS DEFINED IN <linux/limits.h> AND REPRESENTS THE MAX 
LENGTH OF A FILE PATH ON THE CURRENT SYSTEM */

void	free_all(t_data *data)
{
	free(data->input);
	free_array(data->main_input);
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		perror("malloc");
	data->env = init_env(envp);
	data->export = init_export(data);
	data->exit = 0;
	while (42)
	{
		data->input = readline(PURPLE "Minishell> " R);
		if (ft_strlen(data->input) != 0)
			add_history(data->input);
		if (data->input && check_input(data))
			continue ;
		if (!init_data(data))
		{
			start(data);
			free_cmds(data->cmds);
		}
		free_all(data);
	}
	exit(data->exit);
}
