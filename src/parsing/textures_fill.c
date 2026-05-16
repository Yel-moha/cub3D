/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/16 00:00:00 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*trim_texture_path(char **line, int path_index)
{
	char	*trimmed;

	if (!line || !line[path_index])
		return (NULL);
	trimmed = ft_strtrim(line[path_index], " \t\n\r");
	if (!trimmed || !trimmed[0])
	{
		free(trimmed);
		return (NULL);
	}
	return (trimmed);
}

static void	set_texture(char **slot, t_scene *scene, char *flag,
	char *trimmed)
{
	*slot = ft_strdup(trimmed);
	if (*slot)
		update_flags(scene, flag);
}

void	fill_direction_fixed(char **line, t_scene *scene, int path_index)
{
	char	*trimmed;

	trimmed = trim_texture_path(line, path_index);
	if (!trimmed)
		return ;
	if (ft_strncmp(line[0], "NO", 3) == 0 && !scene->textures.no)
		set_texture(&scene->textures.no, scene, "NO", trimmed);
	else if (ft_strncmp(line[0], "SO", 3) == 0 && !scene->textures.so)
		set_texture(&scene->textures.so, scene, "SO", trimmed);
	else if (ft_strncmp(line[0], "WE", 3) == 0 && !scene->textures.we)
		set_texture(&scene->textures.we, scene, "WE", trimmed);
	else if (ft_strncmp(line[0], "EA", 3) == 0 && !scene->textures.ea)
		set_texture(&scene->textures.ea, scene, "EA", trimmed);
	free(trimmed);
}

void	fill_direction(char **line, t_scene *scene)
{
	fill_direction_fixed(line, scene, 1);
}
