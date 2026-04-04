/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/04 11:46:32 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//da cancellare prima di pusciare
#include <stdio.h>

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}



int main(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	**split;
	const char	*map_path;
	t_tex_paths *pos_text;

	pos_text = ft_calloc(1, sizeof(t_tex_paths));
	map_path = "src/valid_minimal.cub";
	if (argc == 2)
		map_path = argv[1];
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("file vuoto o non leggibile: %s\n", map_path);
		close(fd);
		free(pos_text);
		return (1);
	}
	while (line)
	{		
		split = ft_split(line, ' ');
		if (!split || !split[0])
		{
			free_split(split);
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_strncmp(split[0], "F", 2) == 0
			|| ft_strncmp(split[0], "C", 2) == 0)
		{
			char	**rgb_split;

			rgb_split = NULL;
			if (split[1])
				rgb_split = ft_split(split[1], ',');
			if (rgb_split)
			{
				fill_colors(rgb_split);
				free_split(rgb_split);
			}
		}
		fill_direction(split, pos_text);
		free_split(split);
		free(line);
		line = get_next_line(fd);
	}
	print_text_paths(*pos_text);  // debug
	free_paths(pos_text);
	close(fd);
	return (0);
}
