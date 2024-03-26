/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:50:39 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 20:03:31 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* iterates through env and export with the intent of removing
   the defined value received from input */
void	unset_list(t_list **lst, char *str)
{
	int		i;
	int		len;
	t_list	*tmp;

	i = 0;
	tmp = *lst;
	len = ft_lstsize(*lst);
	while (i < len)
	{
		if (ft_strcmp_nochr(str, (char *)tmp->content, '=') == 0
			|| ft_strcmp((char *)tmp->content, str) == 0)
		{
			list_remove(lst, i);
			return ;
		}
		tmp = tmp->next;
		i++;
	}
}

/* sends the second cmd received to unset_list to get it removed */
void	read_unset(t_data *data, char **cmds)
{
	int		i;
	int		len;
	char	*buffer;
	char	*export;

	i = 1;
	len = input_size(cmds);
	while (i < len)
	{
		buffer = ft_strdup(cmds[i]);
		unset_list(data->env, buffer);
		export = export_input(buffer);
		unset_list(data->export, export);
		free(export);
		free(buffer);
		i++;
	}
	data->exit = 0;
}
