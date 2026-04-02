/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/02 15:46:44 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//da cancellare prima di pusciare
#include <stdio.h>
///////////////////////////////


int main(void)
{
    int fd;

    fd = open("valid_minimal.cub", O_RDONLY);
    printf("\n\nIl numero di byte letti e'\n%s\n", get_next_line(fd));
    return (0);
}