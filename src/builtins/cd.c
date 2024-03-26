/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:03:57 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 19:56:07 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* searches for the HOME env variable and changes to it */
void	cd_home(t_data *data)
{
	char	*home;

	home = ft_strtrim(env_grep_value(*data->env, "HOME="), "HOME=");
	if (!home)
	{
		write(2, "error: cd: HOME is undefined\n", 29);
		exit (1);
	}
	else if (chdir(home) != 0)
	{
		perror("cd");
		exit (1);
	}
	else
		data->exit = 0;
	if (home)
		free(home);
}

/* updates the PWD and OLDPWD after a successful cd
   gets the PWD and OLDPWD, stores them in value 
   and uses export to update them */
void	cd_env(t_data *data, char *old_pwd)
{
	char	pwd[PATH_MAX + 1];
	char	**value;

	value = malloc(sizeof(char *) * 4);
	if (!value)
		malloc_error(data);
	ft_bzero(pwd, PATH_MAX + 1);
	getcwd(pwd, sizeof(pwd));
	value[0] = ft_strdup("export");
	value[1] = ft_strjoin("PWD=", pwd);
	value[2] = ft_strjoin("OLDPWD=", old_pwd);
	value[3] = NULL;
	read_export(data, value);
	free_array(value);
	ft_bzero(old_pwd, ft_strlen(old_pwd));
	ft_bzero(pwd, ft_strlen(pwd));
}

/* stores PWD in old_pwd and in case there is an arg
   it changes to it */
void	read_cd(t_data *data, char **path)
{
	char	old_pwd[PATH_MAX + 1];

	ft_bzero(old_pwd, PATH_MAX + 1);
	getcwd(old_pwd, sizeof(old_pwd));
	if (path && input_size(path) > 2)
	{
		write(2, "error: cd: too many arguments\n", 30);
		ft_bzero(old_pwd, ft_strlen(old_pwd));
		data->exit = 1;
		return ;
	}
	else if (!path || !path[1] || !path[1][0])
		cd_home(data);
	else if (chdir(path[1]) != 0)
	{
		perror("cd");
		data->exit = 1;
		return ;
	}
	else
		data->exit = 0;
	cd_env(data, old_pwd);
}
