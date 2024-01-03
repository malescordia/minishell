/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:30:34 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/03 16:23:46 by gude-cas         ###   ########.fr       */
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

typedef struct s_shell
{
    char *input;
}   t_shell;

/* FUNCTIONS */
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(char *s1, char *s2, int n);
char *ft_strcpy(char *str);

/* ENV */
void print_env(char **env);

/* ECHO */
void print_echo(char *str);

#endif
