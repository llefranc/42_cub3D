/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:07:23 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/04 12:23:02 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//on recup le parsing
//creer une fenetre avec une image
//faire du raycasting pour chaque colonne de pixel
//mettre la gestion des events (deplacement dnas la map)
//rajouter les textures
//penser a fermer les flux etc

//verifier pourquoi mettre wall_size car il s'annule dans l'equation. pourtant si je change la hauteur du mur,
//cela ne devrait pas rendre pareil sur l'ecran de projection en theorie ? bien garder en tete que la camera est
//fixee au milieu du mur donc elle si on change auteur du mur ca grandit notre personnage. Mais le mur devriat quand
//meme en theorie ressortir plus grand sur l'ecran de projection non ?

#include "includes/cube3d.h"



//hypothenuse = size_move et j'ai l'angle
//rajouter les collisions


void	move_down_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		mlx->cam->x -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		mlx->cam->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		mlx->cam->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else
	{
		mlx->cam->x -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
}

//cos et sin sont inverses par pour left and right par rapport a up and down
void	move_left_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		mlx->cam->x -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		mlx->cam->x -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		mlx->cam->x += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else
	{
		mlx->cam->x += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
}

void	move_up_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		mlx->cam->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		mlx->cam->x -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		mlx->cam->x -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else
	{
		mlx->cam->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
}

void	move_right_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		mlx->cam->x += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		mlx->cam->x += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		mlx->cam->x -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y -= cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
	else
	{
		mlx->cam->x -= sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
		mlx->cam->y += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE;
	}
}

void	raycasting(t_mlx *mlx)
{
	int		i;
	int		x;
	int		pix_wall;		//number of pixels colored for wall
	int		pix_sky_floor;	//number of pixels colored for sky / floor

	i = -1;
	while (++i < (int)mlx->par->reso[0]) //filling each rows of pixel of the screen (= i)
	{
		x = 0;
		pix_wall = nb_pixel_wall(mlx->cam, 
				positive_angle(mlx->cam->angle + (FOV / 2.0) - mlx->cam->freq_ray * (double)i));
		pix_wall > (int)mlx->par->reso[1] ? pix_wall = (int)mlx->par->reso[1] : 0; //if nb colored pixel walls > resolutinon
		pix_sky_floor = ((int)mlx->par->reso[1] - pix_wall) / 2;
		while (x < pix_sky_floor)				//filling the sky
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = mlx->par->sky_rgb; //filling each line (= x)
		while (x < pix_sky_floor + pix_wall)	//filling the walls
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = 0xFFFF00;
		while (x < (int)mlx->par->reso[1])		//filling the floor
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = mlx->par->flo_rgb;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img->screen, 0, 0); //ici ?
}

int		keypress(int keycode, t_mlx *mlx)
{
	if (keycode == W_KEY)
		move_up_in_map(mlx);
	else if (keycode == S_KEY)
		move_down_in_map(mlx);
	else if (keycode == A_KEY)
		move_left_in_map(mlx);
	else if (keycode == D_KEY)
		move_right_in_map(mlx);
	else if (keycode == LEFT_KEY)
		mlx->cam->angle = positive_angle(mlx->cam->angle + ROTA_SIZE);
	else if (keycode == RIGHT_KEY)
		mlx->cam->angle = positive_angle(mlx->cam->angle - ROTA_SIZE);
	raycasting(mlx);
	return (1);
}

int		drawing(t_pars *par) //l'appeler drawing ? 
{
	t_mlx mlx;
	t_img img;
	t_addr addr;
	t_info info;
	t_rcast cam;
	
	mlx.par = par; //allow to carry only t_mlx struct
	struct_init_mlx(&mlx, &img, &addr, &info); //all *ptr == NULL, all int == -1, link img and addr to mlx
	struct_init_camera(par, &cam); //create a tab of **int for the map, from the prev map in **char. Link par to cam
	mlx.par = par; //allow to carry only t_mlx struct
	mlx.cam = &cam;
	/* infos sur les variables */
	// cam.y -= 0.4;
	// cam.x += 0.35; //valeur contre mur a 5.15, pour faire le test du tuto
	//228 bug
	printf("x = %f et y = %f, angle = %f, distscreen = %f, freq_ray = %f\n", cam.x, cam.y, cam.angle, cam.dist_screen, cam.freq_ray);
	printf("nb_rows = %d et nb_lines = %d\n", cam.nb_rows, cam.nb_lines);
	printf("size line = %d\n", mlx.info->screen[SIZE_LINE]);
	print_map(cam, 1);
	/* infos sur les variables */

	// cam.angle = 228.0;
	// printf("retour pixel wall = %d\n", nb_pixel_wall(&cam, 180.0));

	// double x_len = -243243.5;
	// printf("%d\n", (int)(cam.x + x_len));
	raycasting(&mlx);
	mlx_hook(mlx.win, KEYPRESS, 0, &keypress, &mlx);
	mlx_loop(mlx.ptr);
	return (1);
}