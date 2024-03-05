/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:56:16 by gude-cas          #+#    #+#             */
/*   Updated: 2024/02/21 16:38:25 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parse_env_var(char *input, int i)
{
	if (input[i] == '$')
	{
		i++;
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
			return (parse_quotes(input, input[i], i));
		else if (input[i] && (input[i] != ' ' && input[i] != '\t'
				&& input[i] != '>' && input[i] != '<' && input[i] != '|'
				&& input[i] != '\'' && input[i] != '\"' && input[i] != '$'))
			return (parse_normal(input, i));
	}
	return (i);
}

int	parse_normal(char *input, int i)
{
	if (input[i] && (input[i] != ' ' && input[i] != '\t' && input[i] != '>'
			&& input[i] != '<' && input[i] != '|' && input[i] != '\''
			&& input[i] != '\"' && input[i] != '$'))
	{
		while (input[i] && (input[i] != ' ' && input[i] != '\t'
				&& input[i] != '>' && input[i] != '<' && input[i] != '|'
				&& input[i] != '\'' && input[i] != '\"' && input[i] != '$'))
			i++;
		if (input[i] && input[i] == '$')
			return (parse_env_var(input, i));
		else if (input[i] && (input[i] == '\'' || input[i] == '\"'))
			return (parse_quotes(input, input[i], i));
	}
	return (i);
}

int	parse_quotes(char *input, char quote, int i)
{
	if (input[i] && input[i] == quote)
	{
		i++;
		while (input[i] && input[i] != quote)
			i++;
		if (!input[i])
			return (i);
		i++;
		if (input[i] && (input[i] != ' ' && input[i] != '\t' && input[i] != '>'
				&& input[i] != '<' && input[i] != '|' && input[i] != '\''
				&& input[i] != '\"' && input[i] != '$'))
			return (parse_normal(input, i));
	}
	return (1);
}

int	parse_others(char *input, int i)
{
	if (input[i] && input[i] == '|')
		i++;
	else if (input[i] == '>')
	{
		i++;
		if (input[i] && (input[i] == '>' || input[i] == '|'))
			i++;
	}
	else if (input[i] == '<')
	{
		i++;
		if (input[i] && (input[i] == '<' || input[i] == '>'))
			i++;
	}
	return (i);
}