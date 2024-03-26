/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:40:11 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 19:20:55 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* checks if cmd has any formatting errors: alpha chars, multiple '-'/'+',
	special chars, '-'/'+' out of place */
int	exit_format_error(char *cmd)
{
	char	quotes;
	int		i;
	int		flag;

	i = 0;
	quotes = 0;
	flag = 0;
	while (cmd && cmd[i])
	{
		if (!quotes && cmd[i] && (cmd[i] == '\'' || cmd[i] == '\"'))
			quotes = cmd[i];
		else if (cmd[i] && !flag && (cmd[i] == '-' || cmd[i] == '+'))
			flag = 1;
		else if (cmd[i] && cmd[i] != quotes && !ft_isdigit(cmd[i]))
			return (1);
		else if (quotes && cmd[i] && cmd[i] == quotes)
			quotes = 0;
		i++;
	}
	return (0);
}

int	other_exit_status(char *cmd)
{
	int	n;

	n = ft_atoi(cmd);
	if (n > 0)
	{
		while (n > 256)
			n -= 256;
		return (n);
	}
	else
	{
		while (n < 0)
			n += 256;
		return (n);
	}
}

/* in bash <exit [n]> prints an error if n is larger than LLONG_MAX 
	or smaller then LLONG_MIN */
void	read_exit(t_data *data, char **cmds, int parent)
{
	if (input_size(cmds) >= 2 && cmds[1] && cmds[1][0])
	{
		if (exit_format_error(cmds[1]) || (ft_strchr(cmds[1], '-') \
			&& ft_atoulli(cmds[1]) > (unsigned long long)(LLONG_MAX) + 1) \
			|| ft_atoulli(cmds[1]) > (unsigned long long)(LLONG_MAX))
		{
			ft_putstr_fd("error: exit: ", 2);
			ft_putstr_fd(cmds[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			data->exit = 2;
			free_data(data);
		}
		else if (0 <= ft_atoi(cmds[1]) && ft_atoulli(cmds[1]) <= 255)
			data->exit = (int)ft_atoulli(cmds[1]);
		else
			data->exit = other_exit_status(cmds[1]);
	}
	if (input_size(cmds) > 2)
	{
		ft_putstr_fd("error: exit: too many arguments\n", 2);
		data->exit = 1;
		if (parent)
			return ;
	}
	free_data(data);
}
