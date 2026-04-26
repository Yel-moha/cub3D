/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/26 16:32:57 by yel-moha         ###   ########.fr       */
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

	//x testing
	t_game	game = {0};

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
	if (scene->map.letta != 2)
	{
		free_scene(scene);
		return (1);
	}
	print_text_paths(*scene); // debug
	print_colors(*scene); // debug
	print_player(*scene);
	//printf("il numero di texture e' : %d\n", scene->counter);
	print_split(scene->map.grid);
	//print_grid(*scene);
	//print_map(*scene);

	// x testing - collega scene al game
	game.scene = scene;

	// x testing - INIT ENGINE
	engine_init(&game);
	free_scene(scene);
	return (0);
}
