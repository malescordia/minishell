/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:15:24 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/27 17:43:09 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute(t_data *data, char **cmds)
{
	char	**paths;
	char	*cmd_path;
	char	**env;

	if (!cmds || !cmds[0] || !cmds[0][0])
		write(STDERR_FILENO, "error: '': command not found\n", 29);
	if (is_builtin(cmds[0]))
		read_builtin(data, cmds, 0);
	if (g_signal == SIGPIPE)
		free_data(data);
	if (!cmds || !cmds[0] || !cmds[0][0] || is_builtin(cmds[0]))
		free_data(data);
	paths = get_paths(data->env, cmds[0]);
	if (is_exec(data, cmds[0], paths) == 0)
		free_data(data);
	cmd_path = get_cmd_path(data, paths, cmds[0]);
	free_array(paths);
	if (!cmd_path)
		free_data(data);
	env = list_to_array(data, data->env);
	execve(cmd_path, cmds, env);
	free(cmd_path);
	data->exit = errno;
	free_data(data);
}

/* checks if the cmd is executable and returns the path of the cmd */
char	**get_paths(t_list **env, char *cmd)
{
	int		i;
	t_list	*tmp;
	char	**paths;
	char	**path_dir;

	if (ft_strncmp(cmd, "../", 3) == 0 || ft_strncmp(cmd, "./", 2) == 0 \
		|| cmd[0] == '/')
		return (special_path(cmd));
	tmp = *env;
	while (tmp && ft_strncmp(tmp->content, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	paths = ft_split(tmp->content + 5, ':');
	path_dir = malloc(sizeof(char *) * (input_size(paths) + 1));
	i = 0;
	while (i < input_size(paths))
	{
		path_dir[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	path_dir[i] = NULL;
	free_array(paths);
	return (path_dir);
}

/* checks for a cmd like './minishell' or '../a.out' */
char	**special_path(const char *cmd)
{
	char	**paths;
	char	buffer[PATH_MAX + 1];

	paths = malloc(sizeof(char *) * 2);
	ft_bzero(buffer, PATH_MAX + 1);
	if (ft_strncmp(cmd, "../", 3) == 0 || ft_strncmp(cmd, "./", 2) == 0)
	{
		if (getcwd(buffer, sizeof(buffer)) == NULL)
		{
			free(paths);
			return (NULL);
		}
		paths[0] = ft_strjoin(buffer, "/");
		ft_bzero(buffer, ft_strlen(buffer));
	}
	if (cmd[0] == '/')
		paths[0] = ft_strjoin(NULL, "/");
	paths[1] = NULL;
	return (paths);
}

char	*get_cmd_path(t_data *data, char **paths, char *cmd)
{
	int		i;
	char	*buffer1;
	char	*buffer2;

	i = 0;
	while (paths && paths[i])
	{
		buffer1 = ft_strjoin(paths[i], "/");
		buffer2 = ft_strjoin(buffer1, cmd);
		free(buffer1);
		if (access(buffer2, 0) == 0)
			return (buffer2);
		free(buffer2);
		i++;
	}
	data->exit = 127;
	if (ft_strchr(cmd, '/'))
		perror(cmd);
	else if (ft_strcmp(cmd, "\'\'") != 0 && ft_strcmp(cmd, "\"\"") != 0)
	{
		write(STDERR_FILENO, "error: ", 7);
		ft_putstr_fd(cmd, STDERR_FILENO);
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	return (NULL);
}
