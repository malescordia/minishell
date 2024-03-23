/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:58:30 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/18 15:00:33 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_eof(char *limiter)
{
	ft_putstr_fd("warning: heredoc delimited ", 2);
	ft_putstr_fd("by end_of_file (wanted '", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
}
