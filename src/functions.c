/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:51 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/03 16:23:28 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}

int ft_strcmp(char *s1, char *s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return(*s1 - *s2);
}

int ft_strncmp(char *s1, char *s2, int n)
{
    while(n > 0 && *s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
        n--;
    }
    if(n == 0)
        return(0);
    else
        return(*s1 - *s2);
}

char *ft_strcpy(char *str)
{
    int i = 0;
    char *copy = malloc(sizeof(ft_strlen(str)));
    
    while(str[i])
    {
        copy[i] = str[i];
        i++;
    }
    copy[i] = '\0';
    return(copy);
}