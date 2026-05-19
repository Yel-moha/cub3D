/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 00:00:00 by yel-moha          #+#    #+#             */
/*   Updated: 2026/05/19 21:23:27 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_len_no_nl(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

static char	get_cell(char **rows, int h, int i, int j)
{
	int	len;

	if (i < 0 || i >= h || !rows[i])
		return ('X');
	len = line_len_no_nl(rows[i]);
	if (j < 0 || j >= len)
		return ('X');
	return (rows[i][j]);
}

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	middle_row_is_closed(char **rows, int h, int i)
{
	int	j;
	int	len;

	len = line_len_no_nl(rows[i]);
	j = 0;
	while (j < len)
	{
		if (is_walkable(rows[i][j]) && (get_cell(rows, h, i - 1, j) == 'X'
				|| get_cell(rows, h, i + 1, j) == 'X'
				|| get_cell(rows, h, i, j - 1) == 'X'
				|| get_cell(rows, h, i, j + 1) == 'X'))
			return (0);
		j++;
	}
	return (1);
}
