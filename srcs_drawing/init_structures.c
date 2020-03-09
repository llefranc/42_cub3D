/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:34:54 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 14:45:31 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Getting addresses and informations of each images loaded.
*/
void	struct_init_addr_info(t_mlx *mlx, t_addr *addr, t_info *info)
{
	addr->screen = (int *)mlx_get_data_addr(mlx->img->screen, &(info->screen[BITS_PER_PIX]), 
			&(info->screen[SIZE_LINE]), &(info->screen[ENDIAN]));
	info->screen[SIZE_LINE] /= (info->screen[BITS_PER_PIX] / 8); //to fill the colors with 1 int value and not 3 bytes RGB
	addr->t_no = (int *)mlx_get_data_addr(mlx->img->t_no, &(info->t_no[BITS_PER_PIX]), 
			&(info->t_no[SIZE_LINE]), &(info->t_no[ENDIAN]));
	info->t_no[SIZE_LINE] /= (info->t_no[BITS_PER_PIX] / 8);
	addr->t_so = (int *)mlx_get_data_addr(mlx->img->t_so, &(info->t_so[BITS_PER_PIX]), 
			&(info->t_so[SIZE_LINE]), &(info->t_so[ENDIAN]));
	info->t_so[SIZE_LINE] /= (info->t_so[BITS_PER_PIX] / 8);
	addr->t_ea = (int *)mlx_get_data_addr(mlx->img->t_ea, &(info->t_ea[BITS_PER_PIX]), 
			&(info->t_ea[SIZE_LINE]), &(info->t_ea[ENDIAN]));
	info->t_ea[SIZE_LINE] /= (info->t_ea[BITS_PER_PIX] / 8);
	addr->t_we = (int *)mlx_get_data_addr(mlx->img->t_we, &(info->t_we[BITS_PER_PIX]), 
			&(info->t_we[SIZE_LINE]), &(info->t_we[ENDIAN]));
	info->t_we[SIZE_LINE] /= (info->t_we[BITS_PER_PIX] / 8);
}


/*
** Loading each images. 
*/
void	struct_init_img(t_mlx *mlx, t_info *info)
{
	mlx->img->screen = mlx_new_image(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1]);
	if (!(mlx->img->t_no = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_no, &(info->t_no[WIDTH]), &(info->t_no[HEIGHT]))))
		error_msg("Textures : error loading north texture\n", mlx->par, NULL);
	if (!(mlx->img->t_so = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_so, &(info->t_so[WIDTH]), &(info->t_so[HEIGHT]))))
		error_msg("Textures : error loading south texture\n", mlx->par, NULL);
	if (!(mlx->img->t_ea = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_ea, &(info->t_ea[WIDTH]), &(info->t_ea[HEIGHT]))))
		error_msg("Textures : error loading east texture\n", mlx->par, NULL);
	if (!(mlx->img->t_we = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_we, &(info->t_we[WIDTH]), &(info->t_we[HEIGHT]))))
		error_msg("Textures : error loading west texture\n", mlx->par, NULL);
}

/*
** Join the path of one file and his filename, and then free the path.
*/
void	join_path_filename(t_pars *par, char **path, char *name)
{
	char	*tmp;

	tmp = *path;
	if (!(*path = ft_strjoin(*path, name)))
		error_msg("Malloc failed\n", par, NULL);
	free(tmp);
}

/*
** Add the filename to the path for each textures / sprites.
*/
void	struct_init_paths(t_pars *par)
{
	join_path_filename(par, &(par->path_no), "t_north.xpm");
	join_path_filename(par, &(par->path_so), "t_south.xpm");
	join_path_filename(par, &(par->path_ea), "t_east.xpm");
	join_path_filename(par, &(par->path_we), "t_west.xpm");
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
	struct_init_paths(mlx->par);
	struct_init_img(mlx, info);
	struct_init_addr_info(mlx, addr, info);
}

/*
** Read the map and search for the player position in order to initiate his
** starting position and angle of view. Also save number of max rows for each
** line.
*/
void	init_player_pos(t_rcast *cam)
{
	int		line;
	int		row;

	line = 0;
	while (cam->map[line]) //map is terminated by a NULL *ptr
	{
		row = 0;
		while (cam->map[line][row] != -2)
		{
			if (cam->map[line][row] > 10) //player position
			{
				cam->x = (double)row + 0.5;		//adding 0.5 so the player will start
				cam->y = (double)line + 0.5;	//in the middle of the case
				cam->map[line][row] == EAST ? cam->angle = V_EAST : 0; //0 degees
				cam->map[line][row] == NORTH ? cam->angle = V_NORTH : 0; //90 degrees
				cam->map[line][row] == WEST ? cam->angle = V_WEST : 0; //180 degrees
				cam->map[line][row] == SOUTH ? cam->angle = V_SOUTH : 0; //270 degrees
				cam->map[line][row] = 0;
			}
			row++;
		}
		cam->nb_rows[line] = row; //save number max of rows for each line
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
	int line;

	line = 0;
	struct_init_cam_bool(cam);
	while (par->map[line]) //counting number of lines
		line++;
	cam->nb_lines = line;
	if (!(cam->nb_rows = malloc(line * sizeof(int)))) //for nb rows max for each line
		error_msg("Malloc failed\n", par, NULL);
	cam->map = par->map;
	init_player_pos(cam); //save player position + number of max rows for each line
	cam->dist_screen = (par->reso[0] / 2.0) / tan(((double)FOV / 2.0) * (TO_RAD)); //pythagore, 
	cam->freq_ray = (double)FOV / par->reso[0];
	cam->par = par;	//allow to only carry t_rcast struct
}
