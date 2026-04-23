/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/23 17:23:51 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//da cancellare prima di pusciare
#include <stdio.h>

void
free_split(char **split)
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

static void allocate_scene(t_scene *scene)
{
	scene->flag = ft_calloc(1, sizeof(char));
	if (!scene->flag)
		return ;
	scene->map.width = 0;
	scene->map.height = 0;
	scene->counter = 0;
	scene->pos = 0;
	scene->map.letta = 0;
}
	
int	main(int argc, char **argv)
{
	const char	*map_path;
	t_scene		*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (1);
	allocate_scene(scene);
	if (argc != 2)
	{
		free_scene(scene);
		return (1);
	}
	map_path = argv[1];
	parse_line(map_path, scene);
	print_text_paths(*scene); // debug
	print_colors(*scene); // debug
	print_player(*scene);
	//printf("il numero di texture e' : %d\n", scene->counter);
	print_split(scene->map.grid);
	//print_grid(*scene);
	//print_map(*scene);
	free_scene(scene);
	return (0);
}
