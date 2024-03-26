/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:01:07 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 20:09:34 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* converts the copied env list to an array so execve
   can handle it */
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

/* sorts the export list in ascending order
   to mimic the behaviour of bash */
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

/* removes chosen node from the linked list */
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

/* swap function for list_sort */
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
