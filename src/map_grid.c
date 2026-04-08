/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:17:44 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/08 19:16:48 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void count_grid_height(char *line, t_scene *scene)
{
    size_t j;
    (void) scene;

    j = 0;
    while(line[j] == '1' || line[j] == '0')
            j++;
    if(j == ft_strlen(line) - 1)
        printf("riga composta da soli zeri e uni %s\n", line);
}
