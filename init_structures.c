/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:34:54 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/27 18:47:35 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

/*
** Init a mlx struct, all *ptr will value NULL and all int will value -1.
*/
void	struct_init_mlx(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
	mlx->img_screen = NULL;
	mlx->img_addr = NULL;
	mlx->size_line = -1;
	mlx->endian = -1;
}

/*
** Read the **char map and fill the **int map.
*/
void	transf_map_atoi(t_pars *par, t_rcast *cam)
{
	int		line;
	int		row;

	line = 0;
	while (line < cam->nb_lines)
	{
		row = 0;
		while (row < cam->nb_rows)
		{
			cam->map[line][row] = par->map[line][row] - '0';
			if (cam->map[line][row] > 1) //player position
			{
				cam->x = (double)row + 0.5;		//adding 0.5 so the player will start
				cam->y = (double)line + 0.5;	//in the middle of the case
				par->map[line][row] == 'E' ? cam->angle = V_EAST : 0; //0 degees
				par->map[line][row] == 'N' ? cam->angle = V_NORTH : 0; //90 degrees
				par->map[line][row] == 'W' ? cam->angle = V_WEST : 0; //180 degrees
				par->map[line][row] == 'S' ? cam->angle = V_SOUTH : 0; //270 degrees
				cam->map[line][row] = 0;
			}
			row++;
		}
		line++;
	}
}

/*
** Fill structure cam with the following parameters :
** Number of lines / rows in the map, player position (x, y), angle of view for
** the camera. Also transform the map from **char (in par) to a **int (in cam).
*/
int		**struct_init_camera(t_pars *par, t_rcast *cam)
{
	int row;
	int line;

	row = 0;
	line = 0;
	while (par->map[line]) //counting number of lines
		line++;
	cam->nb_lines = line;
	while (par->map[0][row]) //counting number of rows
		row++;
	cam->nb_rows = row;
	if (!(cam->map = malloc(sizeof(int *) * line)))
		error_msg("Malloc failed\n", par, NULL);
	line = 0;
	while (line < cam->nb_lines)
	{
		if (!(cam->map[line++] = malloc(sizeof(int) * row)))
			error_msg("Malloc failed\n", par, NULL);
	}
	transf_map_atoi(par, cam);
	cam->par = par;
	return (cam->map);
}
