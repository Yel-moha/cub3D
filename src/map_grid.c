/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:17:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/09 14:31:55 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int count_symb(char *line)
{
    int  i;
    int     count;

    i = 0;
    count = 0;
    while(line[i])
    {
        if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            count++;
        i++;
    }
    return (count);
}
void count_grid_height(char *line, t_scene *scene)
{
    size_t j;
    size_t i;

    j = 0;
    i = 0;

    scene->pos += count_symb(line);
    while(line[j] == '1' || line[j] == '0')
        j++;
    if(j == ft_strlen(line) - 1 && j != 0)
        printf("riga composta da soli zeri e uni %s\n", line);
    printf("numeri di simboli pos e' : %d\n", scene->pos);
}
