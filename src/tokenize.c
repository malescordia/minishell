/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:52:25 by gude-cas          #+#    #+#             */
/*   Updated: 2024/03/24 21:05:44 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* returns a cmd with its flags */
char	**tokenizer(t_data *data, char **input, int i)
{
	int		j;
	int		args;
	char	**tmp;

	j = 0;
	args = get_nb_of_args(input, i);
	tmp = malloc(sizeof(char *) * (args + 1));
	if (!tmp)
		malloc_error(data);
	while (input[i] && !input[i][0])
		i++;
	while (j < args)
	{
		if (input[i] && (ft_strcmp(input[i], ">") == 0 \
			|| ft_strcmp(input[i], ">>") == 0 || ft_strcmp(input[i], "<") == 0 \
			|| ft_strcmp(input[i], "<<") == 0))
			i += 2;
		else if (ft_strcmp(input[i], "|") == 0)
			break ;
		else
			j = token_expand(data, tmp, input[i++], j);
	}
	tmp[j] = NULL;
	return (tmp);
}

int	token_expand(t_data *data, char **tmp, char *input, int i)
{
	int		j;
	char	**tmp2;

	j = 0;
	tmp2 = split_input(data, input);
	while (tmp2[j])
	{
		tmp[i] = remove_quotes(tmp2[j]);
		i++;
		j++;
	}
	free_array(tmp2);
	return (i);
}
