/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:01:41 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 22:40:52 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* checks for unclosed quotes */
int	check_quote(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input && input[i])
	{
		if (check_char(input[i]) == 3)
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				ft_putstr_fd("error: unclosed quote\n", STDERR_FILENO);
				return (1);
			}
		}
		if (input[i])
			i++;
	}
	return (0);
}

/* checks for || and |  | */
int	check_pipe(char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] && check_char(input[i]) == 3)
			i = parse_quotes(input, input[i], i);
		else if (input[i] && input[i] == '|')
		{
			i++;
			while (input[i] && check_char(input[i]) == 1)
				i++;
			if (input[i] && input[i] == '|')
				return (print_token_message('|'));
		}
		else
			i++;
	}
	return (0);
}

/* checks for operators at the end of the input */
int	check_end(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0)
	{
		if (input[i] && (input[i] == '<' || input[i] == '>'
				|| input[i] == '|'))
			return (write(2, "error: unexpected token 'newline'\n", 34));
		else if (check_char(input[i]) == 1)
			i--;
		else
			break ;
	}
	return (0);
}

/* checks for >< and <| */
int	check_redir(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input) - 1;
	while (i < len && input[i])
	{
		while (input[i] && input[i] != '>' && input[i] != '<' \
			&& check_char(input[i]) != 3)
			i++;
		if (i < len && input[i] && check_char(input[i]) == 3)
			i = ignore_quotes(input, i);
		if (i < len && input[i] && input[i + 1] && (input[i] == '>' \
				&& input[i + 1] == '<'))
			return (print_token_message(input[i + 1]));
		if (i < len && input[i] && input[i + 1] && (input[i] == '<' \
				&& input[i + 1] == '|'))
			return (print_token_message(input[i + 1]));
		i++;
	}
	return (0);
}

/* checks if there are any >, < or | in sucession (divided by whitespace) */
int	check_order(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input) - 1;
	while (i < len)
	{
		while (input[i] && input[i] != '<' && input[i] != '>' \
			&& check_char(input[i]) != 3)
			i++;
		if (input[i] && i < len && check_char(input[i]) == 3)
			i = ignore_quotes(input, i);
		if (input[i] && (input[i] == '<' || input[i] == '>'))
		{
			i++;
			if (input[i] && i < len && check_char(input[i]) == 1)
			{
				while (input[i] && i < len && check_char(input[i]) == 1)
					i++;
				if (input[i] && check_char(input[i]) == 2)
					return (print_token_message(input[i]));
			}
		}
	}
	return (0);
}
