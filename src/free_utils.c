/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:35:46 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/23 17:23:26 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_paths(t_tex_paths *pos_text)
{
	free(pos_text->no);
	free(pos_text->so);
	free(pos_text->we);
	free(pos_text->ea);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free(scene->textures.ea);
	free(scene->textures.no);
	free(scene->textures.so);
	free(scene->textures.we);
	free_split(scene->map.grid);
	free(scene->flag);
	
	free(scene);
}
