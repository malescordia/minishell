/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:30:52 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 15:12:47 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* splits input into 2D array */
char	**split_input(t_data *data, char *input)
{
	int		i;
	int		len;
	int		words;
	char	**buffer;

	i = 0;
	words = count_words(input);
	buffer = malloc(sizeof(char *) * (words + 1));
	if (!buffer)
		malloc_error(data);
	while (i < words)
	{
		while (*input && check_char(*input) == 1)
			input++;
		len = split_words(input);
		buffer[i++] = split_alloc(data, input, len);
		input = input + len;
	}
	buffer[i] = 0;
	return (buffer);
}

/* return the length of input until the next whitespace
   or separating meta_char */
int	split_words(char *input)
{
	int	i;

	i = 0;
	if (input[i] && check_char(input[i]) == 3)
		return (parse_quotes(input, input[i], i));
	if (input[i] && check_char(input[i]) == 2)
		return (parse_others(input, i));
	if (input[i] && input[i] == '$')
		return (parse_env(input, i));
	if (input[i] && !check_char(input[i]))
		return (parse_normal(input, i));
	return (i);
}

/* allocates memory for the 2D array */
char	*split_alloc(t_data *data, char *input, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		malloc_error(data);
	while (*input && i < len)
		tmp[i++] = *input++;
	tmp[i] = '\0';
	return (tmp);
}

/* how many words does input contain */
int	count_words(char *input)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (input && input[i])
	{
		while (input[i] && check_char(input[i]) == 1)
			i++;
		if (input[i] && check_char(input[i]) != 1)
			words++;
		if (input[i] && check_char(input[i]) == 2)
			i = parse_others(input, i);
		else if (input[i] && check_char(input[i]) == 3)
			i = parse_quotes(input, input[i], i);
		else if (input[i] && input[i] == '$')
			i = parse_env(input, i);
		else if (input[i] && !check_char(input[i]))
			i = parse_normal(input, i);
	}
	return (words);
}
