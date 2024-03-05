/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:27:04 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/05 13:38:34 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_list	**init_env(char **envp)
{
	int		i;
	char	*buffer;
	t_list	*node;
	t_list	**env;

	i = 0;
	env = malloc(sizeof(env));
	*env = NULL;
	while (envp[i])
	{
		buffer = ft_strdup(envp[i]);
		node = ft_lstnew(buffer);
		ft_lstadd_back(env, node);
		i++;
	}
	return (env);
}

void	env_override(char *str, t_list **env)
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
