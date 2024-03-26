/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:16:18 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 20:11:11 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

/* prints export values in order unless theres an arg */
void	export_builtin(t_data *data, char **cmds)
{
	list_sort(data, data->export);
	if (input_size(cmds) > 1)
		read_export(data, cmds);
	else
		list_print(data->export);
}

void	read_builtin(t_data *data, char **cmds, int parent)
{
	if (ft_strcmp(cmds[0], "echo") == 0)
		read_echo(data, cmds);
	else if (ft_strcmp(cmds[0], "cd") == 0)
		read_cd(data, cmds);
	else if (ft_strcmp(cmds[0], "pwd") == 0)
		read_pwd(data);
	else if (ft_strcmp(cmds[0], "exit") == 0)
		read_exit(data, cmds, parent);
	else if (ft_strcmp(cmds[0], "env") == 0)
		list_print(data->env);
	else if (ft_strcmp(cmds[0], "unset") == 0)
		read_unset(data, cmds);
	else if (ft_strcmp(cmds[0], "export") == 0)
		export_builtin(data, cmds);
}
