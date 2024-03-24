/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:57:34 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 22:26:54 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	malloc_error(t_data *data)
{
	ft_putstr_fd("error: malloc failed\n", STDERR_FILENO);
	if (!data)
		exit(12);
	data->exit = 12;
	free_data(data);
}

int	open_error(t_data *data, char *filename, int child)
{
	ft_putstr_fd("error: ", STDERR_FILENO);
	perror(filename);
	if (filename)
		free(filename);
	if (child)
	{
		data->exit = 1;
		free_data(data);
	}
	else
		return (1);
	return (0);
}

void	pipe_error(t_data *data, int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_putstr_fd("error: pipe failed\n", STDERR_FILENO);
	data->exit = 1;
	free_data(data);
}

void	fork_error(t_data *data, int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_putstr_fd("error: fork failed\n", STDERR_FILENO);
	data->exit = 1;
	free_data(data);
}

int	export_error_message(t_data *data, char *error)
{
	data->exit = 1;
	ft_putstr_fd("error: export: '", STDERR_FILENO);
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}
