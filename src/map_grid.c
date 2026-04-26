/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:17:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/26 16:08:49 by yel-moha         ###   ########.fr       */
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

    j = 0;
    scene->pos += count_symb(line, scene);  //Aggiorna il numero dei simboli N, S, E, W all'interno della griglia
    if(scene->pos > 1)
         error_spawn_player(line, scene);  //Esce con errore se c'è piu di una posizione N, S, E, W all'interno della griglia
    while(line[j] == '1' || line[j] == '0' || line[j] == ' '
        || line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
        || line[j] == 'E')
        j++;
    if ((line[j] == '\n' || line[j] == '\0') && j != 0)
        scene->map.height++;  //Aggiorno l'altezza della mappa dopo ogni linea della griglia corretta e non vuota
}

int max_line(char *line, t_scene *scene)
{
    int j;

    j = 0;
    while((line[j] == '1' || line[j] == '0' || line[j] == ' '
            || line[j] == 'N' || line[j] == 'S' || line[j] == 'W'
            || line[j] == 'E') && scene->counter == 6)
        j++;
    return (j);
}
void fill_grid(t_scene *scene, int i, char *line)
{
    int j;

    j = 0;
    while(line[j] != '\0' && line[j] != '\n')
    {
        if(line[j] == ' ') // sostituisco gli spazi all'interno della mappa di uni
            scene->map.grid[i][j] = '1';
        else
            scene->map.grid[i][j] = line[j];
        j++;
    }
    // Qui normalizzo la mappa con uni ma prima di farlo vorrei verificare che fosse valida
    while (j < scene->map.width)
    {
        scene->map.grid[i][j] = '1';
        j++;
    }
    scene->map.grid[i][scene->map.width] = '\0';
}

void allocate_grid(t_scene *scene)
{
    int i;

    i = 0;
    if(scene->map.height > 0)
        scene->map.grid = ft_calloc(scene->map.height + 1, sizeof(char *));
    if(!scene->map.grid)
        return ;
    //scene->map.grid[scene->map.height] = NULL;
    while(i < scene->map.height)
    {
        scene->map.grid[i] = ft_calloc(scene->map.width + 1, sizeof(char));
        if(!scene->map.grid[i])
            return ;
        scene->map.grid[i][scene->map.width] = '\0';
        i++;
    }
}