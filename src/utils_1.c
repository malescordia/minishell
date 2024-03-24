/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:01:07 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 22:24:20 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**list_to_array(t_data *data, t_list **list)
{
	int		i;
	int		len;
	t_list	*tmp;
	char	**buffer;

	i = 0;
	tmp = *list;
	len = ft_lstsize(tmp);
	buffer = malloc(sizeof(char *) * (len + 1));
	if (!buffer)
		malloc_error(data);
	while (tmp && i < len)
	{
		buffer[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}

void	list_sort(t_data *data, t_list **export)
{
	t_list	*head;
	t_list	*tmp;

	head = (*export);
	tmp = head;
	while (tmp)
	{
		while (head->next)
		{
			if (ft_strcmp(head->content, head->next->content) > 0)
				list_swap(data, head);
			head = head->next;
		}
		tmp = tmp->next;
		head = (*export);
	}
}

void	list_remove(t_list **list, int position)
{
	int		i;
	t_list	*tmp;
	t_list	*target;

	i = 0;
	tmp = *list;
	if (position == 0)
	{
		(*list) = (*list)->next;
		free(tmp->content);
		free(tmp);
		return ;
	}
	while (i < position - 1)
	{
		tmp = tmp->next;
		i++;
	}
	target = tmp->next;
	tmp->next = target->next;
	free(target->content);
	free(target);
}

int	list_check_dup(t_list **lst, char *str)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, str) == 0)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void	list_swap(t_data *data, t_list *list)
{
	char	*str;
	t_list	*head;
	t_list	*tmp;

	str = NULL;
	head = list;
	if (!head && !head->next)
	{
		write(2, "List Swap Error\n", 16);
		data->exit = 1;
		return ;
	}
	tmp = head;
	str = tmp->content;
	head->content = head->next->content;
	head->next->content = str;
}
