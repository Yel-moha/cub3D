/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:16:54 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/10 13:20:47 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void update_flags(t_scene *scene, char *flag)
{
	char	*joined;

	joined = ft_strjoin(scene->flag, flag);
	if (!joined)
		return ;
	free(scene->flag);
	scene->flag = joined;
	scene->counter++;
}

void	fill_direction(char **line, t_scene *scene)
{
	if (!line || !line[0] || !line[1])
		return ;
	if (ft_strncmp(line[0], "NO", 3) == 0 && !scene->textures.no)
	{
		scene->textures.no = ft_strdup(line[1]);
		update_flags(scene, "NO");
	}
	else if (ft_strncmp(line[0], "SO", 3) == 0 && !scene->textures.so)
	{
		scene->textures.so = ft_strdup(line[1]);
		update_flags(scene, "SO");
	}
	else if (ft_strncmp(line[0], "WE", 3) == 0 && !scene->textures.we)
	{
		scene->textures.we = ft_strdup(line[1]);
		update_flags(scene, "WE");
	}
	else if (ft_strncmp(line[0], "EA", 3) == 0 && !scene->textures.ea)
	{
		scene->textures.ea = ft_strdup(line[1]);
		update_flags(scene, "EA");
	}
	else
		return ;
}

void	fill_colors(char **line, t_scene *scene, char f_or_c)
{
	if (!line || !line[0] || !line[1] || !line[2])
		return ;
	if (f_or_c == 'F')
	{
		if (ft_strchr(scene->flag, 'F'))
			double_color_path('F', scene, line);
		scene->floor.r = ft_atoi(line[0]);
		scene->floor.g = ft_atoi(line[1]);
		scene->floor.b = ft_atoi(line[2]);
		scene->floor.value = (scene->floor.r << 16)
			| (scene->floor.g << 8) | scene->floor.b;
		update_flags(scene, "F");
	}
	else if (f_or_c == 'C')
	{
		if (ft_strchr(scene->flag, 'C'))
			return ;
		scene->ceiling.r = ft_atoi(line[0]);
		scene->ceiling.g = ft_atoi(line[1]);
		scene->ceiling.b = ft_atoi(line[2]);
		scene->ceiling.value = (scene->ceiling.r << 16)
			| (scene->ceiling.g << 8) | scene->ceiling.b;
		update_flags(scene, "C");
	}
}

// Questa funzione avra il compito di verficare il codice dei vari colori r g b
/*
static int check_colors_value(char **line)
{
	int ret;

	if (!line || !line[0] || !line[1] || !line[2])
		return (0);
	
}
		*/
