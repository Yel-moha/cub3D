/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:48:58 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/07 16:13:30 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **parse_textures(char *line, t_tex_paths *pos)
{
    int         fd;
    char        **split;
    char        *line;
    t_tex_paths *pos_text;

    pos_text = ft_calloc(1, sizeof(t_tex_paths));
    fd = open(map_path, O_RDONLY);
    line = get_next_line(fd);
	if (!line)
	{
		printf("file vuoto o non leggibile: %s\n", map_path);
		free(pos_text);
		return (1);
	}
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

void  line_errors(char *line, int fd)
{
    if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (!line)
	{
		printf("file vuoto o non leggibile: %s\n", map_path);
		close(fd);
		free(pos_text);
		return (1);
	}
}
char **parse_colors(char **line)
{
    
}