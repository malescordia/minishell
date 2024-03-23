/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:23:38 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/18 11:58:11 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*value_iter(t_data *data, char *value)
{
	char	*buffer;
	t_list	*tmp;

	if (ft_strcmp(value, "?") == 0)
	{
		buffer = ft_itoa(data->exit);
		return (buffer);
	}
	tmp = *data->env;
	while (tmp)
	{
		buffer = value_cmp((char *)tmp->content, value);
		if (buffer)
			return (buffer);
		tmp = tmp->next;
		free(buffer);
	}
	return (NULL);
}

char	*value_cmp(char *env, char *value)
{
	char	*tmp1;
	char	*tmp2;

	if (!value)
		return (NULL);
	if (ft_strcmp_nochr(value, env, '=') == 0)
	{
		tmp1 = ft_strfront_trim(env, value);
		tmp2 = ft_strfront_trim(tmp1, "=");
		free(tmp1);
		return (tmp2);
	}
	return (NULL);
}

char	*env_grep_value(t_list *env, char *value)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->content)
	{
		if (ft_strncmp((char *)tmp->content, value, ft_strlen(value)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->content);
}
