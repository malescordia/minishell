/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:36:43 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/26 13:38:29 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_input(t_data *data)
{
	if (check_quote(data->input) || check_pipe(data->input) || \
		check_start(data->input) || check_end(data->input) \
		|| check_redir(data->input) || check_double_redir(data->input) \
		|| check_dollar(data->input) || check_order(data->input) \
		|| check_tokens(data->input))
	{
		free(data->input);
		data->exit = 2;
		return (1);
	}
	return (0);
}

/* checks for | at the start of the input */
int	check_start(char *input)
{
	int	i;

	i = 0;
	while (input[i] && check_char(input[i]) == 1)
		i++;
	if (input[i] && input[i] == '|')
		return (print_token_message(input[i]));
	return (0);
}

/* checks for & ( ) ; */
int	check_tokens(char *input)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (i < (int)ft_strlen(input))
	{
		if (check_char(input[i]) == 3)
			i += ignore_quotes(input, i);
		if (i < (int)ft_strlen(input) && (input[i] == '&' || input[i] == '(' \
			|| input[i] == ')' || input[i] == ';'))
			c = input[i];
		i++;
	}
	if (c != 0)
		return (print_token_message(c));
	return (0);
}

/* checks for $$ and handles the dollar case of single quotes */
int	check_dollar(char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (!input[i])
				break ;
			i++;
		}
		else if (input[i] == '$' && input[i + 1] == '$')
			return (print_token_message('$'));
		else
			i++;
	}
	return (0);
}

/* checks for << | and for >> | */
int	check_double_redir(char *input)
{
	int		i;
	int		len;
	char	redir;

	i = 0;
	len = ft_strlen(input) - 1;
	while (i < len)
	{
		while (i < len && check_char(input[i]) != 3 && input[i] != '>' \
				&& input[i] != '<')
			i++;
		if (i < len && input[i] && check_char(input[i]) == 3)
			i = ignore_quotes(input, i);
		if (i < len && input[i] && i < len && (input[i] == '>'
				|| input[i] == '<'))
		{
			redir = input[i];
			if (i < len && input[i + 1] == redir && (input[i + 2] == '|'
					|| (input[i + 2] == ' ' \
					&& input[i + 3] == '|')))
				return (print_token_message('|'));
		}
		i++;
	}
	return (0);
}
