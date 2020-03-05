/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:56:38 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/05 10:38:07 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Check if the line contains only map characters. If it's the case, return 1
** to indicate it's a map line. Return 0 otherwise.
*/
int		key_map_line(t_pars *par, char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (!ft_strchr("012NSWE ", line[i]) && !par->map)
			return (0);
		else if (!ft_strchr("012NSWE ", line[i]) && par->map)
			error_msg("File .cub, map : must only contains ' 012NSWE' characters\n", par, line);
	}
	return (1);
}

/*
** Check the first characters of the line and look if it's a key or an empty
** line. Otherwise print error msg and exit.
*/
int		key_type(char *line, t_pars *par)
{
	if (line[0] == 'R' && line[1] == ' ')
		return (RESO);
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (P_NORTH);
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (P_SOUTH);
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (P_EAST);
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (P_WEST);
	else if (line[0] == 'S' && line[1] == ' ')
		return (P_SPRIT);
	else if (line[0] == 'F' && line[1] == ' ')
		return (FLO_RGB);
	else if (line[0] == 'C' && line[1] == ' ')
		return (SKY_RGB);
	else if (line[0] == '\0') //in the case of a \n
	{
		if (par->reso[0] == -1 && !par->path_no && !par->path_so && !par->path_ea
			&& !par->path_we && !par->path_sp && par->flo_rgb == -1
			&& par->sky_rgb == -1 && !par->map)
			error_msg("File .cub : must begin by one element\n", par, line);
		return (0);
	}
	else if (key_map_line(par, line))
		return (MAP_LINE);
	else //if the beginning of a line ins't a key or isn't empty, error
		error_msg("File .cub, keys : wrong key, or some lines between keys aren't empty\n"
		"Expected keys : 'R', 'NO', 'SO', 'EA', 'WE', 'S', 'F', 'C' followed by at least\n"
		"one space and first line of the map containing only ' 012NSWE' characters\n", par, line);
	return (-1); 
}

/*
** Return the number of missing keys.
*/
int		numbers_key_missing(t_pars *par)
{
	int i;

	i = 0;
	par->reso[0] == -1 ? i++ : 0;
	!par->path_no ? i++ : 0;
	!par->path_so ? i++ : 0;
	!par->path_ea ? i++ : 0;
	!par->path_we ? i++ : 0;
	!par->path_sp ? i++ : 0;
	par->flo_rgb == -1 ? i++ : 0;
	par->sky_rgb == -1 ? i++ : 0;
	!par->map ? i++ : 0;
	return (i);
}

/*
** Call the function error_msg if one or several keys are missing.
*/
void	key_check(t_pars *par)
{
	if (numbers_key_missing(par) > 1)
		error_msg("File .cub, keys : several keys are missing. Expected keys :\n"
		"'R ', 'NO ', 'SO ', 'EA ', 'WE ', 'S ', 'F ', 'C ',\n"
		"and first line of the map containing only ' 012NSWE' characters\n", par, NULL);
	else if (par->reso[0] == -1)
		error_msg("File .cub, resolution : 'R ' key is missing\n", par, NULL);
	else if (!par->path_no)
		error_msg("File .cub, path : 'NO ' key is missing\n", par, NULL);
	else if (!par->path_so)
		error_msg("File .cub, path : 'SO ' key is missing\n", par, NULL);
	else if (!par->path_ea)
		error_msg("File .cub, path : 'EA ' key is missing\n", par, NULL);
	else if (!par->path_we)
		error_msg("File .cub, path : 'WE ' key is missing\n", par, NULL);
	else if (!par->path_sp)
		error_msg("File .cub, path : 'S ' key is missing\n", par, NULL);
	else if (par->flo_rgb == -1)
		error_msg("File .cub, colors : 'F ' key is missing\n", par, NULL);
	else if (par->sky_rgb == -1)
		error_msg("File .cub, colors : 'C ' key is missing\n", par, NULL);
	else if (!par->map)
		error_msg("File .cub, map : Map is missing\n", par, NULL);
}
