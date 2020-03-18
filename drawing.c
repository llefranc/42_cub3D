/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:07:23 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/18 18:47:34 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ORDRE EXECUTION TACHES
//on recup le parsing
//creer une fenetre avec une image
//faire du raycasting pour chaque colonne de pixel
//mettre la gestion des events (deplacement dnas la map)
//rajouter les textures
//mettre les sprites

//EN PLUS
//revoir les lags en grosse resolution
//voir le deformement des murs
//penser a free les sprites
//rajouter plusieurs sprites
//revoir pourquoi errored line marche pas des fois
//ex : 
/*
111111111111111111111111111111111
1000000000000000100000200001111111
1000000000000100100200S0002001001
10000000000001000000W020001111111
111111111111111111111111111111111
*/

#include "includes/cube3d.h"

/*
** Moving in texture's adress and returning the color of one pixel of the
** texture, depending of which side of the wall is touched by the ray.
** We start from a certain row (depending where the ray touch the wall, if the
** ray touch at 33% of the wall we will start at row WALL_SIZE / 3), then we
** choose the line with start_line + freq_pixel.
*/
int		draw_texture(t_mlx *mlx, t_texture *textu, int x)
{
	int		color;

	x = (int)((double)x * textu->freq_pixel);
	x >= mlx->info->t_no[WIDTH] ? x = mlx->info->t_no[WIDTH] - 1 : 0; //for avoiding segfault when round error with double
	if (textu->side_wall == NORTH)
		color = mlx->addr->t_no[textu->row_img + textu->start_line_img * mlx->info->t_no[SIZE_LINE]
					+ x * mlx->info->t_no[SIZE_LINE]];
	if (textu->side_wall == SOUTH)
		color = mlx->addr->t_so[textu->row_img + textu->start_line_img * mlx->info->t_so[SIZE_LINE]
					+ x * mlx->info->t_so[SIZE_LINE]];
	if (textu->side_wall == EAST)
		color = mlx->addr->t_ea[textu->row_img + textu->start_line_img * mlx->info->t_ea[SIZE_LINE]
					+ x * mlx->info->t_ea[SIZE_LINE]];
	if (textu->side_wall == WEST)
		color = mlx->addr->t_we[textu->row_img + textu->start_line_img * mlx->info->t_we[SIZE_LINE]
					+ x * mlx->info->t_we[SIZE_LINE]];
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
** Launches a ray for each row of pixel and calculates the height of the wall
** in pixel. Then color the row with the sky_color, wall with the texture and
** floor with floor color by moving ih the memory of the image with a *int ptr.
*/
void	raycasting(t_mlx *mlx)
{
	int				i;
	unsigned int	x;
	double			pix_wall;		//number of pixels colored for wall
	double			pix_sky_floor;	//number of pixels colored for sky / floor
	t_texture		textu;

	i = -1;
	calc_sprites_orientation(mlx->spri, mlx->cam->angle); //orientation of sprite's plan
	while (++i < (int)mlx->par->reso[0]) //filling each rows of pixel of the screen (= i)
	{
		x = 0;
		reset_ray_len_sprites(mlx->spri); //put all rays len, nb_pix and row_percent to -1.0
		pix_wall = nb_pixel_wall(mlx, mlx->cam, &textu,
				positive_angle(mlx->cam->angle + (FOV / 2.0) - mlx->cam->freq_ray * (double)i));
		texture_resizing(mlx, &textu, &pix_wall);
		pix_sky_floor = (mlx->par->reso[1] - pix_wall) / 2.0;
		while (x < (unsigned int)pix_sky_floor)				//filling the sky
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = mlx->par->sky_rgb; //filling each line (= x)
		while (x < (unsigned int)(pix_sky_floor + pix_wall))	//filling the walls with textures
		{
			mlx->addr->screen[i + x * mlx->info->screen[SIZE_LINE]] = draw_texture(mlx, &textu, x - pix_sky_floor);
			x++;
		}
		while (x < (unsigned int)mlx->par->reso[1])		//filling the floor
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = mlx->par->flo_rgb;
		draw_sprites(mlx, mlx->spri, i);	//sort tab of struct sprites and draw them in the correct order
	}
}

int		drawing(t_pars *par) //l'appeler drawing ? 
{
	t_mlx mlx;
	t_img img;
	t_addr addr;
	t_info info;
	t_rcast cam;
	
	print_map(par->map);
	mlx.par = par; //allow to carry only t_mlx struct
	mlx.cam = &cam; //allow to carry only t_mlx struct
	struct_init_mlx(&mlx, &img, &addr, &info); //all *ptr == NULL, all int == -1, link img info and addr to mlx
	struct_init_camera(&mlx, &cam, par); //create a tab of **int for the map, from the prev map in **char. Link par to cam

	// cam.x -= 0.1;
	// cam.y -= 0.1;
	/* infos sur les variables */
	printf("x = %f et y = %f, angle = %f, distscreen = %f, freq_ray = %f\n", cam.x, cam.y, cam.angle, cam.dist_screen, cam.freq_ray);
	printf("size line = %d\n", mlx.info->screen[SIZE_LINE]);
	/* infos sur les variables */

	/* infos sur les sprites */
	// int i = -1;
	// while (mlx.spri[++i])
	// 	printf("type = %d, x = %d, y = %d\n", mlx.spri[i]->type, mlx.spri[i]->x, mlx.spri[i]->y);
	/* infos sur les sprites */

	// calc_sprites_orientation(mlx.spri, cam.angle);
	// printf("xa = %f, ya = %f, xb = %f, yb = %f\n", mlx.spri[0]->a.x, mlx.spri[0]->a.y, mlx.spri[0]->b.x, mlx.spri[0]->b.y);
	// reset_ray_len_sprites(mlx.spri); //put all rays len, nb_pix and row_percent to -1.0
	
	// t_texture textu;
	// x_ray_len(&mlx, &cam, cam.angle, &textu);
	// y_ray_len(&mlx, &cam, cam.angle, &textu);
	// draw_sprites(&mlx, mlx.spri);
	// printf("ray_len = %f, rowimg = %f\n", mlx.spri[0]->ray_len, mlx.spri[0]->row_percent);
	
	raycasting(&mlx); //allow to print first image
	mlx_put_image_to_window(mlx.ptr, mlx.win, mlx.img->screen, 0, 0); //ici ?

	mlx_hook(mlx.win, MOTIONNOTIFY, 0, &motion_notify, &mlx); //configure fonction pour deplacement souris
	mlx_hook(mlx.win, KEYPRESS, 0, &key_press, &mlx); //configure fonction quand on presse une touche
	mlx_hook(mlx.win, KEYRELEASE, 0, &key_release, &mlx); //configure fonction quand on relache une touche
	mlx_hook(mlx.win, DESTROYNOTIFY, 0, &destroy_notify, par); //configure fonction quand on ferme une fenetre
	mlx_loop_hook(mlx.ptr, &no_event, &mlx); //configure fonction quand pas d'evenements. Permet de print
	mlx_loop(mlx.ptr);
	return (1);
}