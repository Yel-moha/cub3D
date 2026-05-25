/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/02 17:22:27 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	allocate_scene(t_scene *scene)
{
	scene->flag = ft_calloc(1, sizeof(char));
	if (!scene->flag)
		return ;
	scene->player = ft_calloc(1, sizeof(t_player));
	if (!scene->player)
		return ;
	scene->map.width = 0;
	scene->map.height = 0;
	scene->counter = 0;
	scene->pos = 0;
	scene->map.letta = 0;
}

static void	map_format(const char *map_path)
{
	size_t	len;

	if (!map_path)
	{
		write(2, "Errore formato mappa\n", 21);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(map_path);
	if (len < 4 || ft_strncmp(&(map_path[len - 4]), ".cub", 5) != 0)
	{
		write(2, "Errore formato mappa\n", 21);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	const char	*map_path;
	t_scene		*scene;
	t_game		game;

	game = (t_game){0};
	if (argc != 2)
		return (1);
	map_path = argv[1];
	map_format(map_path);
	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		return (1);
	allocate_scene(scene);
	parse_line(map_path, scene);
	if (scene->map.letta != 2)
	{
		free_scene(scene);
		return (1);
	}
	game.scene = scene;
	engine_init(&game);
	free_scene(scene);
	return (0);
}
