/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 20:57:54 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/09 10:58:06 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Check if there is no spaces at the end of lines.
*/
void	check_spaces_end_of_line(t_pars *par, char *line, int key)
{
	int i;

	i = 0;
	while (line[i])
		i++;
	if (i && line[i - 1] == ' ') //if i means if not empty line
	{
		key == RESO ? error_msg("File .cub, resolution : Spaces"
				" at the end of 'R' line are not allowed\n", par, line) : 0;
		key == P_NORTH ? error_msg("File .cub, path : Spaces"
				" at the end of 'NO' line are not allowed\n", par, line) : 0;
		key == P_SOUTH ? error_msg("File .cub, path : Spaces"
				" at the end of 'SO' line are not allowed\n", par, line) : 0;
		key == P_EAST ? error_msg("File .cub, path : Spaces"
				" at the end of 'EA' line are not allowed\n", par, line) : 0;
		key == P_WEST ? error_msg("File .cub, path : Spaces"
				" at the end of 'WE' line are not allowed\n", par, line) : 0;
		key == P_SPRIT ? error_msg("File .cub, path : Spaces"
				" at the end of 'S' line are not allowed\n", par, line) : 0;
		key == P_B_FLOOR ? error_msg("File .cub, path : Spaces"
				" at the end of 'FB' line are not allowed\n", par, line) : 0;
		key == P_B_SKY ? error_msg("File .cub, path : Spaces"
				" at the end of 'CB' line are not allowed\n", par, line) : 0;
		key == P_B_DOOR ? error_msg("File .cub, path : Spaces"
				" at the end of 'DB' line are not allowed\n", par, line) : 0;
		key == FLO_RGB ? error_msg("File .cub, colors : Spaces"
				" at the end of 'F' line are not allowed\n", par, line) : 0;
		key == SKY_RGB ? error_msg("File .cub, colors : Spaces"
				" at the end of 'C' line are not allowed\n", par, line) : 0;
	}
}

/*
** Call the right fonction to do the parsing of the elements depending on the
** value of the key.
*/
int		parse_func(t_pars *par, char *line, int key)
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
	else if (key == P_B_FLOOR)
		ret = parse_path(par, &(par->path_b_fl), line);
	else if (key == P_B_SKY)
		ret = parse_path(par, &(par->path_b_sk), line);
	else if (key == P_B_DOOR)
		ret = parse_path(par, &(par->path_b_do), line);
	else if (key == FLO_RGB)
		ret = parse_flo_rgb(par, line);
	else if (key == SKY_RGB)
		ret = parse_sky_rgb(par, line);
	return (ret);
}

/*
** Parse the map file and fill the *par structure with : 
** resolution, NO/SO/EA/WE/S/B_FL/B_SK/B_DO paths, floor and sky RGB colors, the map.
*/
int		parsing(t_pars *par)
{
	char	*line;
	int		ret;
	int		key;

	line = NULL;
	ret = 1;
	while (ret > 0 && key != MAP_LINE) //first parse the elements
	{
		ret = get_next_line(par->fd, &line);
		key = key_type(line, par); //check also if 'R' is the first line of the file
		check_spaces_end_of_line(par, line, key); //print error_msg if spaces at the end of lines
		if (parse_func(par, line, key) == -1) //call the right parse_function
			error_msg("Malloc failed\n", par, line);
		if (key == MAP_LINE) //if we meet the first line
			parse_map(par, line); //converts to int the line and add new int_line to par->map
		free(line);
	}
	while (ret > 0 && key == MAP_LINE) //then parse the map
	{
		ret = get_next_line(par->fd, &line);
		key = key_type(line, par);
		key == MAP_LINE ? parse_map(par, line) : 0;  //converts to int the line and add new int_line to par->map
		free(line);
	}
	if (!key) //no empty lines authorized after map
		error_msg("File .cub, map : must end the file and be followed by nothing\n", par, NULL);
	else if (key && key != MAP_LINE) //if line isn't empty and isn't a map line
		error_msg("File .cub, map : must only contains ' 0123456789NSWE' characters\n", par, NULL);
	key_check(par); //check if keys are missing in the file
	map_check(par); //check if the map is correct
	return (1);
}
