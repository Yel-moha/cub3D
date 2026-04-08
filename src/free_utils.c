/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-moha <yel-moha@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:35:46 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/08 11:20:12 by yel-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_paths(t_tex_paths *pos_text)
{
    free(pos_text->no);
	free(pos_text->so);
	free(pos_text->we);
	free(pos_text->ea);
	free(pos_text);
}

void free_scene(t_scene *scene)
{
	if(!scene)
		return ;
	while(scene)
	{
		//if(scene->textures)
			free(scene->textures.ea);
			free(scene->textures.no);
			free(scene->textures.so);
			free(scene->textures.we);
		
	}
}