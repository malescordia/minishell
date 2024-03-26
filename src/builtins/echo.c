/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:33:11 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 18:28:43 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* checks for '-n' */
int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

/* prints content after i */
void	print_echo(char **cmds, int i)
{
	int	j;

	while (cmds && i < input_size(cmds))
	{
		j = 0;
		while (j < (int)ft_strlen(cmds[i]) && cmds[i][j])
		{
			if (cmds[i][j])
				printf("%c", cmds[i][j++]);
		}
		i++;
		if (cmds && cmds[0]
			&& i < input_size(cmds))
			printf(" ");
	}
}

/* echo executor */
int	read_echo(t_data *data, char **cmds)
{
	int		i;
	int		cmd_args;
	int		flag;

	i = 1;
	flag = 0;
	data->exit = 0;
	cmd_args = input_size(cmds);
	while (cmds[i] && check_flag(cmds[i]))
	{
		flag = 1;
		i++;
	}
	print_echo(cmds, i);
	if (cmd_args == 1)
		return (printf("\n"));
	if (!flag)
		printf("\n");
	return (0);
}
