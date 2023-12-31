/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:30:34 by gude-cas          #+#    #+#             */
/*   Updated: 2023/12/31 16:44:20 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>

/* LIB */
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(char *s1, char *s2, int n);

#endif
