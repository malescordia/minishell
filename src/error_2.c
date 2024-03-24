/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:58:30 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/03/24 15:31:39 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_eof(char *limiter)
{
	ft_putstr_fd("warning: heredoc delimited ", STDERR_FILENO);
	ft_putstr_fd("by end_of_file (wanted '", STDERR_FILENO);
	ft_putstr_fd(limiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}
