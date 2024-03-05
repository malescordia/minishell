/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:52:25 by gude-cas          #+#    #+#             */
/*   Updated: 2024/02/22 17:06:35 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// cmd_with_flags
char	**tokenizer(char **input, int i)
{
	int		j;
	int		args;
	char	**tmp;

	j = 0;
	args = get_args_nb(input, i);
	tmp = malloc(sizeof(char *) * (args + 1));
	if (!tmp)
		perror("malloc");
	while (input[i] && !input[i][0])
		i++;
	while (j < args)
	{
		if (ft_strcmp(input[i], ">") == 0 || ft_strcmp(input[i], ">>") == 0
			|| ft_strcmp(input[i], "<") == 0 || ft_strcmp(input[i], "<<") == 0)
			i += 2;
		else if (ft_strcmp(input[i], "|") == 0)
			break ;
		else
			i = token_expand(tmp, input[j++], i);
	}
	tmp[i] = NULL;
	return (tmp);
}

// split_expansion
int	token_expand(char **tmp, char *input, int i)
{
	int		j;
	char	**tmp2;

	j = 0;
	tmp2 = split_input(input);
	while (tmp2[j])
	{
		tmp[i] = remove_quotes(tmp2[j]);
		i++;
		j++;
	}
	free_array(tmp2);
	return (i);
}
