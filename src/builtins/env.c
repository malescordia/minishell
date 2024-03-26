/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:27:04 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 13:32:31 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* creates a linked list storing copys of the env variables */
t_list	**init_env(char **envp)
{
	int		i;
	char	*tmp;
	t_list	*node;
	t_list	**env;

	i = 0;
	env = (t_list **)malloc(sizeof(env));
	*env = NULL;
	while (envp[i])
	{
		tmp = ft_strdup(envp[i]);
		node = ft_lstnew(tmp);
		ft_lstadd_back(env, node);
		i++;
	}
	return (env);
}

/* checks if there is str already in env, if there is 
	that env variable value gets updated */
void	check_env(char *str, t_list **env)
{
	t_list	*tmp;
	t_list	*node;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strchr(str, '='))
			break ;
		if (ft_strcmp_chr((char *)tmp->content, str, '=') == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(str);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp && ft_strchr(str, '='))
	{
		node = ft_lstnew(ft_strdup(str));
		ft_lstadd_back(env, node);
	}
}
