/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/07 16:03:55 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **parse_textures(char *line, t_tex_paths *pos)
{
    char        **split;
    char        *line;
    t_tex_paths *pos;

    while(line)
    {
        split = ft_split(line, ' ');
        split_errors(split);
    }
}
void split_errors(char **split)
{
    if(!split || !split[0])
    {
        free_split(split);
    }
}

void  line_errors(char *line)
{
    
}
char **parse_colors(char **line)
{
    
}