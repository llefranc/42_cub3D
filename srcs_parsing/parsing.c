/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:57:54 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/18 18:21:42 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Init the structure by putting char * to NULL and for each tab of int by
** putting each value of tabs to -1, so we can check during the parsing if we
** already have treated the parameter or not.
*/
void	struct_init(t_cube *par)
{
	par->fd = -1;
	par->reso[0] = -1;
	par->reso[1] = -1;
	par->path_no = NULL;
	par->path_so = NULL;
	par->path_ea = NULL;
	par->path_we = NULL;
	par->path_sp = NULL;
	par->flo_rgb[0] = -1;
	par->flo_rgb[1] = -1;
	par->flo_rgb[2] = -1;
	par->sky_rgb[0] = -1;
	par->sky_rgb[1] = -1;
	par->sky_rgb[2] = -1;
	par->map = NULL;
}

/*
** Allow to free each elements of the structure, including each line of **map
** and close the file descriptor.
*/
void	struct_free(t_cube *par)
{
	int i;

	i = -1;
	par->fd != -1 ? close(par->fd) : 0; //if there is a flux, we close it
	free(par->path_no);
	free(par->path_so);
	free(par->path_ea);
	free(par->path_we);
	free(par->path_sp);
	if (par->map)
	{
		while (par->map[++i]) // until we reach the NULL *ptr in map
			free(par->map[i]);
		free(par->map);
	}
}

/*
** Call the right fonction to do the parsing of the elements depending on the
** value of the key.
*/
int		parse_func(t_cube *par, char *line, int key)
{
	int		ret;

	ret = 1;
	if (key == RESO)
		ret = parse_reso(par, line);
	else if (key == P_NORTH)
		ret = parse_path(par, &(par->path_no), line);
	else if (key == P_SOUTH)
		ret = parse_path(par, &(par->path_so), line);
	else if (key == P_EAST)
		ret = parse_path(par, &(par->path_ea), line);
	else if (key == P_WEST)
		ret = parse_path(par, &(par->path_we), line);
	else if (key == P_SPRIT)
		ret = parse_path(par, &(par->path_sp), line);
	else if (key == FLO_RGB)
		ret = parse_flo_rgb(par, line);
	else if (key == SKY_RGB)
		ret = parse_sky_rgb(par, line);
	return (ret);
}

/*
** Parse the map file and fill the *par structure with : 
** resolution, NO/SO/EA/WE/S paths, floor and sky RGB colors, the map.
*/
int		parsing(t_cube *par)
{
	char	*line;
	int		ret;
	int		key;

	line = NULL;
	ret = 1;
	while (ret > 0 && key != MAP_LINE) //first parse the elements
	{
		ret = get_next_line(par->fd, &line);
		key = key_type(line, par);
		if (parse_func(par, line, key) == -1) //call the right parse_function
			error_msg("Error\nMalloc failed\n", par, line);
		if (key == MAP_LINE) //if we met the first line
			parse_map(par, line); //we trim the spaces and add new trim_line to par->map
		free(line);
	}
	while (ret > 0 && key == MAP_LINE) //then parse the map
	{
		ret = get_next_line(par->fd, &line);
		key = key_type(line, par);
		if (key && key != MAP_LINE) //if line isn't empty and doesn't begin by a 1
			error_msg("Error\nFile .cub, map : each line must begin by '1'\n", par, line);
		key == MAP_LINE ? parse_map(par, line) : 0; //trim the spaces and add a new trim_line to par->map
		free(line);
	}
	while (ret > 0) //then parse the rest of the file
	{
		ret = get_next_line(par->fd, &line);
		if (line && line[0] != '\0')
			error_msg("Error\nFile .cub, map : must be followed only by empty lines\n", par, line);
		free(line);
	}
	key_check(par); //check if keys are missing in the file
	map_check(par); //check if the map is correct
	return (1);
}
