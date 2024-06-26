/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:41:40 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 19:11:00 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* prints cwd and resets all elements of it to zero */
void	read_pwd(t_data *data)
{
	char	cwd[PATH_MAX + 1];

	ft_bzero(cwd, PATH_MAX + 1);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", getcwd(cwd, sizeof(cwd)));
		ft_bzero(cwd, ft_strlen(cwd));
	}
	else
	{
		perror("pwd");
		data->exit = errno;
		return ;
	}
	data->exit = 0;
}
