/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-cas <gude-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 15:42:48 by gude-cas          #+#    #+#             */
/*   Updated: 2024/01/03 16:28:51 by gude-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void print_echo(char *str)
{
    int i = 5;
    int j = 0;
    char *var = malloc(sizeof(10));
    while(str[i])
    {
        if(str[i] == '$')
        {
            i++;
            while(str[i] && (str[i] != ' ' && str[i] != '\t'))
            {
                var[j] = str[i];
                j++;
                i++;
            }
            printf("%s", getenv(var));
        }
        else
            printf("%c", str[i]);
        i++;
    }
    printf("\n");
}
