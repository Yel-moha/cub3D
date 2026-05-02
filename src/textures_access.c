/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 14:28:06 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/02 17:41:58 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int textures_exist(t_scene *scene)
{
    if (!scene->textures.ea || access(scene->textures.ea, F_OK) != 0)
        return (0);
    if (!scene->textures.no || access(scene->textures.no, F_OK) != 0)
        return (0);
    if (!scene->textures.so || access(scene->textures.so, F_OK) != 0)
        return (0);
    if (!scene->textures.we || access(scene->textures.we, F_OK) != 0)
        return (0);
    return (1);
}

void textures_error_path(t_scene *scene)
{
	if (!scene)
		exit(EXIT_FAILURE);
	get_next_line(-1);
	write(1, "Errore textures\n", ft_strlen("Errore textures") + 1);
	free_scene(scene);
	exit(EXIT_FAILURE);
}