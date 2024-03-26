/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:19:05 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 20:18:57 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* a copy of the env variables list to handle the export builtin
   it prepends each variable with "declare -x" */
t_list	**init_export(t_data *data)
{
	int		i;
	char	*tmp;
	t_list	**export;
	t_list	*node;
	t_list	*env_buffer;

	i = 0;
	export = (t_list **)malloc(sizeof(export));
	if (!export)
		malloc_error(data);
	*export = NULL;
	env_buffer = (*data->env);
	while (i < ft_lstsize((*data->env)))
	{
		tmp = export_input(env_buffer->content);
		node = ft_lstnew(tmp);
		ft_lstadd_back(export, node);
		env_buffer = env_buffer->next;
		i++;
	}
	list_sort(data, export);
	return (export);
}

/* parses export arguments, checks for anything 
   different from an alphanumeric or a '_' */
int	export_error(t_data *data, char *input)
{
	int	i;

	i = 0;
	if (ft_isdigit(input[0]) || input[0] == '=')
		return (export_error_message(data, input));
	while (i < (int)ft_strlen(input) && input[i] != '=')
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (export_error_message(data, input));
		i++;
	}
	return (0);
}

/* takes input and creates new string in specific format
   "declare -x variablename=variablevalue" */
char	*export_input(char *input)
{
	int		i;
	int		j;
	int		len;
	char	*buffer1;
	char	*buffer2;

	i = 0;
	j = 0;
	len = ft_strlen(input);
	buffer1 = ft_calloc(len + 3, sizeof(char));
	while (input[i] && input[i] != '=')
		buffer1[j++] = input[i++];
	buffer1[j++] = input[i++];
	buffer1[j++] = '\"';
	while (i < len)
		buffer1[j++] = input[i++];
	buffer1[j] = '\"';
	buffer2 = ft_strjoin("declare -x ", buffer1);
	free(buffer1);
	return (buffer2);
}

/* returns 1 if there is already an env variable with the same name as input
   returns 0 if it doesn't find a match */
int	check_export(char *input, t_list **export)
{
	char	*buffer;
	t_list	*tmp;

	tmp = *export;
	buffer = export_input(input);
	while (tmp)
	{
		if (!ft_strchr(buffer, '=') && ft_strcmp_nochr(buffer, tmp->content, \
			'=') == 0)
			break ;
		if (ft_strcmp_chr(tmp->content, buffer, '=') == 0 || \
			(!ft_strchr(tmp->content, '=') && ft_strcmp_nochr(tmp->content, \
			buffer, '=') == 0))
		{
			free(tmp->content);
			tmp->content = ft_strdup(buffer);
			break ;
		}
		tmp = tmp->next;
	}
	free(buffer);
	if (!tmp)
		return (0);
	return (1);
}

/* creates a new env variable */
void	read_export(t_data *data, char **input)
{
	int		i;
	t_list	*node;

	i = 1;
	while (i < input_size(input))
	{
		if (export_error(data, input[i]))
		{
			i++;
			continue ;
		}
		check_env(input[i], data->env);
		if (check_export(input[i], data->export) == 1)
		{
			i++;
			continue ;
		}
		node = ft_lstnew(export_input(input[i]));
		ft_lstadd_back(data->export, node);
		i++;
	}
}
