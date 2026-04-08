/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:32:37 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/08 14:57:13 by yel-moha         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	const char	*map_path;
	t_scene		*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (argc != 2)
		return (1);
	map_path = argv[1];
	parse_line(map_path, scene);
	//print_text_paths(*scene); // debug
	//print_colors(*scene); // debug
	free_scene(scene);
	return (0);
}
