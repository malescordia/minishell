/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:40:48 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/04 18:58:51 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_executable(t_data *data, char *cmd, char *cmd_path, char **paths)
{
	struct stat	path_stat;

	stat(cmd_path, &path_stat);
	if (S_ISDIR(path_stat.st_mode) != 0)
	{
		ft_putstr_fd("error: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		data->exit = 126;
	}
	else if (access(cmd_path, X_OK) == 0)
	{
		free(cmd_path);
		return (1);
	}
	else if (access(cmd_path, X_OK) != 0)
	{
		perror("access");
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
	char	*buffer;
	char	*buffer2;

	i = 0;
	if (!paths)
		return (1);
	while (paths[i])
	{
		buffer = ft_strjoin(paths[i++], "/");
		buffer2 = ft_strjoin(buffer, cmd);
		free(buffer);
		if (access(buffer2, F_OK) == 0)
			return (is_executable(data, cmd, buffer2, paths));
		free(buffer2);
	}
	return (1);
}
