/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcapa-pe <gcapa-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:39:45 by gcapa-pe          #+#    #+#             */
/*   Updated: 2024/02/21 15:41:04 by gcapa-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main() {
    FILE *file;
    char ch;


    file = fopen("start_img.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }

    fclose(file);

    return 0;
}
