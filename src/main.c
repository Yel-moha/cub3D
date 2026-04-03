/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/03 18:25:26 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//da cancellare prima di pusciare
#include <stdio.h>

static void	free_split(char **split)
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
		is_valid_direction(split, pos_text);
		print_split(split);
		//free_split(split);
		free(line);
		line = get_next_line(fd);
	}
	//free(line);
	print_text_paths(*pos_text);
	free(pos_text->no);
	free(pos_text->so);
	free(pos_text->we);
	free(pos_text->ea);
	free(pos_text);
	free_split(split);
	close(fd);
	return (0);
}