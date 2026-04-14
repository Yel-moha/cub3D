/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:17:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/14 17:54:04 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int count_symb(char *line, t_scene *scene)
{
    int  i;
    int     count;

    i = 0;
    count = 0;
    while(line[i])
    {
        if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            count++;
            scene->player.spawn = line[i];
        }
        i++;
    }
    return (count);
}
void count_grid_height(char *line, t_scene *scene)
{
    size_t j;

    j = 0;
    scene->pos += count_symb(line, scene);
    if(scene->pos > 1)
        printf("Errore spawn giocatore %d\n", scene->pos);
    while(line[j] == '1' || line[j] == '0' || line[j] == ' ')
        j++;
    printf("j == %zu \n", j);
    if ((line[j] == '\n' || line[j] == '\0') && j != 0)
    if(j == ft_strlen(line) - 1 && j != 0)
        printf("riga composta da soli zeri e uni %s\n", line);
    if(j == ft_strlen(line))
        printf("riga composta da soli zeri e uni %s\n", line);
}
int max_line(char *line, t_scene *scene)
{
    int j;

    j = 0;
    while((line[j] == '1' || line[j] == '0' || line[j] == ' '
            || line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
            || line[j] == 'E') && scene->counter == 6)
        j++;
    if(j != 0)
        scene->map.height++;
    return (j);
}