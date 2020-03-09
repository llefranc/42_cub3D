/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:07:23 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 12:32:20 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ORDRE EXECUTION TACHES
//on recup le parsing
//creer une fenetre avec une image
//faire du raycasting pour chaque colonne de pixel
//mettre la gestion des events (deplacement dnas la map)
//rajouter les textures

//EN PLUS
//rajouter nom du fichier
//revoir un peu les noms des parametres dans init struct
//revoir les deplacements en diagonal

//verifier pourquoi mettre wall_size car il s'annule dans l'equation. pourtant si je change la hauteur du mur,
//cela ne devrait pas rendre pareil sur l'ecran de projection en theorie ? bien garder en tete que la camera est
//fixee au milieu du mur donc elle si on change auteur du mur ca grandit notre personnage. Mais le mur devriat quand
//meme en theorie ressortir plus grand sur l'ecran de projection non ?

#include "includes/cube3d.h"

/*
** Launches a ray for each row of pixel and calculates the height of the wall
** in pixel. Then color the row with the sky_color, wall color and floor color
** by moving ih the memory of the image with a *int ptr.
*/
void	raycasting(t_mlx *mlx)
{
	int		i;
	unsigned int	x;
	unsigned int	pix_wall;		//number of pixels colored for wall
	unsigned int	pix_sky_floor;	//number of pixels colored for sky / floor

	i = -1;
	while (++i < (int)mlx->par->reso[0]) //filling each rows of pixel of the screen (= i)
	{
		x = 0;
		pix_wall = nb_pixel_wall(mlx->cam, 
				positive_angle(mlx->cam->angle + (FOV / 2.0) - mlx->cam->freq_ray * (double)i));
		pix_wall > (unsigned int)mlx->par->reso[1] ? pix_wall = (unsigned int)mlx->par->reso[1] : 0; //if nb colored pixel walls > resolutinon
		pix_sky_floor = ((int)mlx->par->reso[1] - pix_wall) / 2;
		while (x < pix_sky_floor)				//filling the sky
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = mlx->par->sky_rgb; //filling each line (= x)
		while (x < pix_sky_floor + pix_wall)	//filling the walls
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = 0xFFFF00;
		while (x < (unsigned int)mlx->par->reso[1])		//filling the floor
			mlx->addr->screen[i + x++ * mlx->info->screen[SIZE_LINE]] = mlx->par->flo_rgb;
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
	struct_init_camera(par, &cam); //create a tab of **int for the map, from the prev map in **char. Link par to cam

	/* infos sur les variables */
	printf("x = %f et y = %f, angle = %f, distscreen = %f, freq_ray = %f\n", cam.x, cam.y, cam.angle, cam.dist_screen, cam.freq_ray);
	printf("size line = %d\n", mlx.info->screen[SIZE_LINE]);
	/* infos sur les variables */


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