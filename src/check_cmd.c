/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:40:48 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/27 17:35:51 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* stat is used to validate if the cmd is a file and
	check if it isnt a directory */
int	is_usable(t_data *data, char	*cmd, char *cmd_path, char **paths)
{
	struct stat	path_stat;

	stat(cmd_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode) != 0)
	{
		ft_putstr_fd("error: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		data->exit = 126;
	}
	else if (access(cmd_path, X_OK) == 0)
	{
		free(cmd_path);
		return (1);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		perror("error: access:");
		data->exit = 126;
	}
	else
		data->exit = 1;
	free(cmd_path);
	free_array(paths);
	return (0);
}

int	is_exec(t_data *data, char *cmd, char **paths)
{
	int		i;
	char	*buffer1;
	char	*buffer2;

	i = 0;
	if (!paths)
		return (1);
	while (paths[i])
	{
		buffer1 = ft_strjoin(paths[i++], "/");
		buffer2 = ft_strjoin(buffer1, cmd);
		free(buffer1);
		if (access(buffer2, F_OK) == 0)
			return (is_usable(data, cmd, buffer2, paths));
		free(buffer2);
	}
	return (1);
}
