/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:34:54 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/04 17:22:09 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

/*
** Getting addresses and informations of each images loaded.
*/
void	struct_init_addr_info(t_mlx *mlx, t_addr *addr, t_info *info)
{
	addr->screen = (int *)mlx_get_data_addr(mlx->img->screen, &(info->screen[BITS_PER_PIX]), 
			&(info->screen[SIZE_LINE]), &(info->screen[ENDIAN]));
	info->screen[SIZE_LINE] /= (info->screen[BITS_PER_PIX] / 8); //to fill the colors with 1 int value and not 3 bytes RGB
}

/*
** Loading each images.
*/
void	struct_init_img(t_mlx *mlx)
{
	mlx->img->screen = mlx_new_image(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1]);
}

/*
** Init a mlx struct. Create a mlx->ptr with mlx_init() and a new window for
** mlx->win, links addr, img, info structures to mlx. Loads the differents
** images on mlx->img, and filled the addresses and informations of those
** images in respectively mlx->addr and mlx->info.
*/
void	struct_init_mlx(t_mlx *mlx, t_img *img, t_addr *addr, t_info *info)
{
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1], "cub3d");
	mlx->img = img;
	mlx->addr = addr;
	mlx->info = info;
	struct_init_img(mlx);
	struct_init_addr_info(mlx, addr, info);
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

void	struct_init_cam_bool(t_rcast *cam)
{
	cam->m_up = 0;		//booleans for movements
	cam->m_down = 0;
	cam->m_left = 0;
	cam->m_right = 0;
	cam->r_left = 0;	//booleans for rotations
	cam->r_right = 0;
	cam->mouse_bool = 0; //first use of the mouse
	cam->mouse_x = 0;	 //x position of the mouse
}

/*
** Fill structure cam with the following parameters :
** Number of lines / rows in the map, player position (x, y), angle of view for
** the camera. Also transform the map from **char (in par) to a **int (in cam).
*/
void	struct_init_camera(t_pars *par, t_rcast *cam)
{
	int row;
	int line;

	row = 0;
	line = 0;
	struct_init_cam_bool(cam);
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
	cam->dist_screen = (par->reso[0] / 2.0) / tan(((double)FOV / 2.0) * (TO_RAD)); //pythagore, 
		//cam->dist_screen : dist between cam (who's launching rays) and screen of projection
	cam->freq_ray = (double)FOV / par->reso[0];
	cam->par = par;	//allow to only carry t_rcast struct
}
