/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:17:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/15 12:09:15 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int count_symb(char *line, t_scene *scene)
{
    int  i;
    int     count;
    char    c;

    i = 0;
    count = 0;
    while(line[i])
    {
        if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            count++;
            c = line[i];
        }
        i++;
    }
    if(count == 1)
        scene->player.spawn = c;
    return (count);
}

void count_grid_height(char *line, t_scene *scene)
{
    size_t j;
    int     i;

    j = 0;
    i = 0;
    scene->pos += count_symb(line, scene);
    if(scene->pos > 1)
         error_spawn_player(line, scene);
    while(line[j] == '1' || line[j] == '0' || line[j] == ' ')
        j++;
    if ((line[j] == '\n' || line[j] == '\0') && j != 0)
    if(j == ft_strlen(line) - 1 && j != 0)
    {
        fill_grid(scene, i, line);
        i++;
    }
    if(j == ft_strlen(line) && j == (size_t)scene->map.width)
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
void fill_grid(t_scene *scene, int i, char *line)
{
    
    int j;

    j = 0;
    allocate_grid(scene);
    while(line)
    {
        if(line[j] == ' ')
            scene->map.grid[i][j] = '1';
        else
            scene->map.grid[i][j] = line[j];
        j++;
    }
}

void allocate_grid(t_scene *scene)
{
    int i;

    i = 0;
    if(scene->map.height > 0)
        scene->map.grid = malloc(sizeof(char *) * scene->map.height + 1);
    if(!scene->map.grid)
        return ;
    scene->map.grid[scene->map.height] = '\0';
    while(i < scene->map.height);
    {
        scene->map.grid[i] = malloc(sizeof(char) * scene->map.width);
        if(!scene->map.grid[i])
            return ;
        scene->map.grid[i][scene->map.width] = '\0';
        i++;
    }
}