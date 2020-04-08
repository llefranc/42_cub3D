/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:07:23 by llefranc          #+#    #+#             */
/*   Updated: 2020/04/08 10:08:12 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Moving in texture's adress and returning the color of one pixel. We start
** from a certain row (depending where the ray touched the wall, if the
** ray touched at 33% of the wall we will start at row WALL_SIZE / 3), then we
** choose the line with start_line + freq_pixel.
*/
int		tex_color(t_mlx *mlx, int x, int pix_row, int pix_line)
{
	int		color;

	if (mlx->textu->side_wall == NORTH)
		color = mlx->addr.t_no[mlx->textu->row_img + pix_row + mlx->textu->start_line_img * mlx->info.t_no[SIZE_LINE]
				+ x * mlx->info.t_no[SIZE_LINE] + pix_line * mlx->info.t_no[SIZE_LINE]];
	if (mlx->textu->side_wall == SOUTH)
		color = mlx->addr.t_so[mlx->textu->row_img + pix_row + mlx->textu->start_line_img * mlx->info.t_so[SIZE_LINE]
				+ x * mlx->info.t_so[SIZE_LINE] + pix_line * mlx->info.t_no[SIZE_LINE]];
	if (mlx->textu->side_wall == EAST)
		color = mlx->addr.t_ea[mlx->textu->row_img + pix_row + mlx->textu->start_line_img * mlx->info.t_ea[SIZE_LINE]
				+ x * mlx->info.t_ea[SIZE_LINE] + pix_line * mlx->info.t_no[SIZE_LINE]];
	if (mlx->textu->side_wall == WEST)
		color = mlx->addr.t_we[mlx->textu->row_img + pix_row + mlx->textu->start_line_img * mlx->info.t_we[SIZE_LINE]
				+ x * mlx->info.t_we[SIZE_LINE] + pix_line * mlx->info.t_no[SIZE_LINE]];
	return (color);
}

/*
** Moving in texture's adress and returning the color of one pixel of the
** texture, depending of which side of the wall is touched by the ray / and the
** level choose. If it's a door side / level doesn't matter.
*/
int		draw_texture(t_mlx *mlx, t_texture *textu, int x)
{
	int		color;
	int		side;
	int		lev;

	side = textu->side_wall;
	lev = mlx->eve.level;
	x = (int)((double)x * mlx->textu->freq_pixel);
	x >= mlx->info.t_no[WIDTH] ? x = mlx->info.t_no[WIDTH] - 1 : 0; //for avoiding segfault when round error with double
	side == NORTH && lev == 1 ? color = tex_color(mlx, x, T1_NORTH_R, T1_NORTH_L) : 0;
	side == NORTH && lev == 2 ? color = tex_color(mlx, x, T2_NORTH_R, T2_NORTH_L) : 0;
	side == NORTH && lev == 3 ? color = tex_color(mlx, x, T3_NORTH_R, T3_NORTH_L) : 0;
	side == SOUTH && lev == 1 ? color = tex_color(mlx, x, T1_SOUTH_R, T1_SOUTH_L) : 0;
	side == SOUTH && lev == 2 ? color = tex_color(mlx, x, T2_SOUTH_R, T2_SOUTH_L) : 0;
	side == SOUTH && lev == 3 ? color = tex_color(mlx, x, T3_SOUTH_R, T3_SOUTH_L) : 0;
	side == EAST && lev == 1 ? color = tex_color(mlx, x, T1_EAST_R, T1_EAST_L) : 0;
	side == EAST && lev == 2 ? color = tex_color(mlx, x, T2_EAST_R, T2_EAST_L) : 0;
	side == EAST && lev == 3 ? color = tex_color(mlx, x, T3_EAST_R, T3_EAST_L) : 0;
	side == WEST && lev == 1 ? color = tex_color(mlx, x, T1_WEST_R, T1_WEST_L) : 0;
	side == WEST && lev == 2 ? color = tex_color(mlx, x, T2_WEST_R, T2_WEST_L) : 0;
	side == WEST && lev == 3 ? color = tex_color(mlx, x, T3_WEST_R, T3_WEST_L) : 0;
	if (side == DOOR)
		color = mlx->addr.t_do[textu->row_img + textu->start_line_img * mlx->info.t_do[SIZE_LINE]
					+ x * mlx->info.t_do[SIZE_LINE]];
	return (color);
}

/*
** Allow to resize the texture by calculating at which frequence each pixel
** has to be print. Textures have a size of 64 pixels.
** Exemple : if pix_wall value 192, each 3 screen's pixels will have the color
** of 1 texture's pixel.
*/
void	texture_resizing(t_mlx *mlx, t_texture *textu, double *pix_wall)
{
	int		pix_wall2;

	textu->no_limit_pix_wall = (int)*pix_wall;
	*pix_wall > mlx->par->reso[1] ? *pix_wall = mlx->par->reso[1] : 0; //if nb colored pixel walls > resolution
	pix_wall2 = (int)*pix_wall;
	if (pix_wall2 >= textu->no_limit_pix_wall) //the whole wall will fit in the screen
	{
		textu->start_line_img = 0; //we start from the beginning of the texture since we will print it entirely
		textu->freq_pixel = (double)WALL_SIZE / (double)pix_wall2;
	}
	else	//wall is taller than what we can print on screen. We will print only a portion of the texture
	{
		textu->start_line_img = (WALL_SIZE - (int)((double)WALL_SIZE *			//if no_limit == 400 and pix_wall == 200
					(double)pix_wall2 / (double)textu->no_limit_pix_wall)) / 2;	//then we have to start at 25% of the img texture
		textu->freq_pixel = (double)(WALL_SIZE - 2 * textu->start_line_img) / (double)pix_wall2;
	}
}

/*
** Draw on the screen first x pixels of sky texture / color, x pixels of walls'
** texture, and then x pixels of floor texture / color.
*/
void	drawing_sky_wall_floor(t_mlx *mlx, t_texture *textu, int i, unsigned int pix_wall)
{
	unsigned int	x;				//to fill each line of the pixel's row
	unsigned int	pix_sky_floor;

	x = 0;
	pix_sky_floor = (unsigned int)((mlx->par->reso[1] - pix_wall) / 2.0);
	pix_wall += pix_sky_floor;
	while (x < pix_sky_floor)				//filling the sky
	{
		if (mlx->eve.print_texture)					//printing either textures or RGB color
			mlx->addr.screen[i + x * mlx->info.screen[SIZE_LINE]] = 
				draw_skybox(mlx, mlx->par->reso[1] - (double)x, 
				positive_angle(mlx->cam->angle + (FOV / 2.0) - mlx->cam->freq_ray * (double)i));
		else
			mlx->addr.screen[i + x * mlx->info.screen[SIZE_LINE]] = mlx->par->sky_rgb;
		x++;
	}
	while (x < pix_wall)	//filling the walls with textures
	{
		mlx->addr.screen[i + x * mlx->info.screen[SIZE_LINE]] = draw_texture(mlx, textu, x - pix_sky_floor);
		x++;
	}
	while (x < (unsigned int)mlx->par->reso[1])		//filling the floor
	{
		if (mlx->eve.print_texture)					//printing either textures or RGB color
			mlx->addr.screen[i + x * mlx->info.screen[SIZE_LINE]] = 
				floor_raycasting(mlx, (double)x - mlx->par->reso[1] / 2.0, 
				positive_angle(mlx->cam->angle + (FOV / 2.0) - mlx->cam->freq_ray * (double)i));
		else
			mlx->addr.screen[i + x * mlx->info.screen[SIZE_LINE]] = mlx->par->flo_rgb;
		x++;
	}
}

/*
** Launches a ray for each row of pixel and calculates the height of the wall
** in pixel. Then color the row with this order : sky > walls > floor > sprites.
*/
void	raycasting(t_mlx *mlx)
{
	int			i;
	double		pix_wall;		//number of pixels colored for wall
	t_texture	textu;

	i = -1;
	mlx->textu = &textu;
	calc_sprites_orientation(mlx->spri, mlx->cam->angle); //orientation of sprite's plan
	while (++i < (int)mlx->par->reso[0]) //filling each rows of pixel of the screen (= i)
	{
		reset_ray_len_sprites(mlx->spri); //put all rays len, nb_pix and row_percent to -1.0
		pix_wall = nb_pixel_wall(mlx, mlx->cam, &textu,
				positive_angle(mlx->cam->angle + (FOV / 2.0) - mlx->cam->freq_ray * (double)i));
		texture_resizing(mlx, &textu, &pix_wall);
		drawing_sky_wall_floor(mlx, &textu, i, (unsigned int)pix_wall);
		draw_sprites(mlx, mlx->spri, i);	//sort tab of struct sprites and draw them in the correct order
	}
}

/*
** Initiates all the structures, the player's informations, loads the textures
** and sprites. Save if asked the first image rendered and exit ; otherwise 
** attributes one fucntion for each event, and creates a loop with mlx_loop
** on those 5 functions.
*/
int		drawing(t_pars *par, int save)
{
	t_mlx	mlx;
	t_rcast	cam;
	
	mlx.par = par; //allow to carry only t_mlx struct
	mlx.cam = &cam; //allow to carry only t_mlx struct
	struct_init_mlx(&mlx); //all *ptr == NULL, all int == -1,
	struct_init_camera(&mlx, &cam, par); //Link par to cam and initiates player position
	raycasting(&mlx); //first image for save
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.screen, 0, 0);
	if (save)
		save_image_as_bmp(&mlx); //will save first image as bmp and then exit the programm
	mlx.eve.level = 0; //to print and stay in level menu until player choose a level
	draw_level_menu(&mlx); //then we draw the level menu
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img.screen, 0, 0);
	mlx_hook(mlx.win, MOTIONNOTIFY, 0, &motion_notify, &mlx); //rotate camera with mouse
	mlx_hook(mlx.win, KEYPRESS, 0, &key_press, &mlx); //player's movements + rotation, shooting, interacting..
	mlx_hook(mlx.win, KEYRELEASE, 0, &key_release, &mlx); //same than keypress
	mlx_hook(mlx.win, DESTROYNOTIFY, 0, &destroy_notify, &mlx); //exit properly the program when closing window
	mlx_loop_hook(mlx.ptr, &no_event, &mlx); //actualize player's position, raycasting + drawing
	mlx_loop(mlx.ptr); //loop on the 5 previous mlx_hook events
	return (1);
}