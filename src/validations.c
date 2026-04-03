/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:16:54 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/03 18:23:06 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void is_valid_direction(char **line, t_tex_paths *pos)
{
    if (ft_strncmp(line[0], "NO", 3) == 0)
        pos->no = line[1];
    else if (ft_strncmp(line[0], "SO", 3) == 0)
        pos->so = line[1];
    else if (ft_strncmp(line[0], "WE", 3) == 0)
        pos->we = line[1];
    else if (ft_strncmp(line[0], "EA", 3) == 0)
        pos->ea = line[1];
}