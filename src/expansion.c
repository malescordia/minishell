/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:58:45 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 16:17:53 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* replaces env variables with their value */
char	**expander(t_data *data)
{
	int		arr_index;
	int		new_index;
	char	*value;
	char	**new_input;

	value = NULL;
	arr_index = 0;
	new_index = 0;
	new_input = ft_calloc(sizeof(char *), input_size(data->main_input) + 1);
	while (data->main_input[arr_index])
	{
		if (!ft_strchr(data->main_input[arr_index], '$'))
		{
			new_input[new_index] = ft_strdup(data->main_input[arr_index]);
			new_index++;
			arr_index++;
			continue ;
		}
		value = get_value(data, data->main_input[arr_index++]);
		if (value && value[0])
			new_input[new_index++] = ft_strdup(value);
		free(value);
	}
	new_input[new_index] = NULL;
	return (new_input);
}

/* helper for get_value function */
char	*substitute_value(t_data *data, char *result, char quotes, int i)
{
	char	*value;
	char	*tmp;
	char	*buffer;

	value = NULL;
	tmp = NULL;
	buffer = NULL;
	tmp = ft_strndup(result, i);
	if (!(check_char(result[i + 1]) == 3 && !quotes))
		buffer = ft_strndup(result + i, \
		get_variable_len(result + i));
	if (buffer && ft_strcmp(buffer, "$") == 0)
		value = ft_strdup(buffer);
	else if (buffer)
		value = find_value(data, buffer + 1);
	free(buffer);
	buffer = ft_strjoin(tmp, value);
	free(tmp);
	tmp = ft_strdup(result + i + get_variable_len(result + i));
	free(value);
	free(result);
	result = ft_strjoin(buffer, tmp);
	free(buffer);
	free(tmp);
	return (result);
}

/* replaces an env variable with its value */
char	*get_value(t_data *data, char *str)
{
	int		i;
	int		len;
	char	quotes;
	char	*result;

	len = 0;
	quotes = '\0';
	i = 0;
	result = ft_strdup(str);
	while (result && result[i])
	{
		if (!quotes && check_char(result[i]) == 3)
			quotes = result[i];
		else if (quotes && result[i] == quotes)
			quotes = '\0';
		if (result[i] == '$' && quotes != '\'')
		{
			len = get_index(data, result, quotes, i);
			result = substitute_value(data, result, quotes, i);
			i += len - 1;
		}
		i++;
	}
	return (result);
}

int	get_index(t_data *data, char *result, char quotes, int i)
{
	int		j;
	char	*value;
	char	*buffer;

	value = NULL;
	buffer = NULL;
	j = 0;
	if (!(check_char(result[i + 1]) == 3 && !quotes))
		buffer = ft_strndup(result + i, \
		get_variable_len(result + i));
	if (buffer && ft_strcmp(buffer, "$") == 0)
		value = ft_strdup(buffer);
	else if (buffer)
		value = find_value(data, buffer + 1);
	j = ft_strlen(value);
	free(buffer);
	free(value);
	return (j);
}

/* if $? return 2 
   if $3 replace with NULL 
   while str[i] is alphanumerical or '_' i++ 
   returns the length of the variables name */
int	get_variable_len(char *str)
{
	int	i;

	i = 0;
	if (check_char(str[i]) != 4)
		return (0);
	i++;
	if (str[i] && (str[i] == '?' || ft_isdigit(str[i])))
		return (2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}
