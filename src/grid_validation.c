 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anacotti <anacotti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:25:04 by yel-moha          #+#    #+#             */
/*   Updated: 2026/04/23 17:38:07 by anacotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	line_len_no_nl(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}
//h : qui come parametro e' l'altezza della mappa
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
//h : qui come parametro e' l'altezza della mappa
static int	middle_row_is_closed(char **rows, int h, int i)
{
	int	j;
	int	len;
	char	c;

	//Calcolo qui la lughezza della linea passatami di indice i
	len = line_len_no_nl(rows[i]);
	j = 0;
	// ciclo sul singolo sul 11111111singolo carattere i,j con j fissato 
	while (j < len)
	{
		c = rows[i][j];
		//se il singolo carattere e' camminabile e se
			//
		if (is_walkable(c) && (get_cell(rows, h, i - 1, j) == 'X'
				|| get_cell(rows, h, i + 1, j) == 'X'
				|| get_cell(rows, h, i, j - 1) == 'X'
				|| get_cell(rows, h, i, j + 1) == 'X'))
			return (0);
		j++;
	}
	return (1);
}

static void	free_rows(char **rows, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(rows[i]);
		i++;
	}
	free(rows);
}

static int	load_map_rows(const char *map_path, t_scene *scene, char **rows)
{
	int		fd;
	int		grid_i;
	char	*line;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (line_errors(NULL, fd), -1);
	grid_i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line) && grid_i < scene->map.height)
			rows[grid_i++] = ft_strdup(line); // Carico le righe corrette 
			//della matrice via via che esistono e sono valide
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (grid_i);// torna il numero delle righe della griglia
}

int	validate_borders(const char *map_path, t_scene *scene)
{
	char	**rows; //Matrice dentro la quale copiero la griglia
	int		i;
	int		loaded;

	rows = ft_calloc(scene->map.height + 1, sizeof(char *)); //Alloco la matrice
	//che conterra la griglia 
	if (!rows)
		return (0);
	loaded = load_map_rows(map_path, scene, rows); //carica la griglia all'interno della rows
	if (loaded != scene->map.height) // Errore se load_map torna un numero diverso dalla altezza della griglia precedentemente caricata
		return (free_rows(rows, loaded), 0);
	if (!validate_line(rows[0], 0, scene)) // validazione della prima linea della griglia
		return (free_rows(rows, loaded), 0);
	if (!validate_line(rows[scene->map.height - 1], scene->map.height - 1, scene))// validazione dell'ultima linea della griglia
		return (free_rows(rows, loaded), 0);
	i = 1; //Importantissimo i = 1, al fine di entrare nella funzione middle_row_is_closed successivamente
	//Qui siamo nella parte interna della matrice, 
	while (i < scene->map.height - 1)
	{
		if (!validate_line(rows[i], i, scene))
			return (free_rows(rows, loaded), 0);
		if (!middle_row_is_closed(rows, scene->map.height, i))
			return (free_rows(rows, loaded), 0);
		i++;
	}
	free_rows(rows, loaded);
	return (1);
}

int	validate_line(char *line, int index, t_scene *scene)
{
	int	j;
	int	end_line;

	j = 0;
	if (index == 0 || index == scene->map.height - 1)
	{
		end_line = line_len_no_nl(line);
		while (line[j] == '1' || line[j] == ' ')
			j++;
		if (j == end_line && j != 0)
			return (1);
		return (0);
	}
	///////scarto linee fatte di soli spazi////
	end_line = line_len_no_nl(line);
	while (line[j] == ' ')
		j++;
	if (j == end_line)
		return (0);
	if (line[j] != '1')
		return (0);
	//////////////////////////////////////////
	//trimmo gli spazzi a fine linea
	while (end_line > 0 && line[end_line - 1] == ' ')
		end_line--;
	// se una linea e' fatta di soli spazi oppure il suo ultimo carattere
	//non e' uno allora e' riga sbagliata
	if (end_line <= 0 || line[end_line - 1] != '1')
		return (0);
	//se niente di cio accade torno 1 (ovvero riga valida)
	return (1);
}
