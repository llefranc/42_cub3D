/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 17:54:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/20 12:21:59 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"



/*
dans l'ordre:
- on descend a chaque fois d'un pixel. ca nous donne donc une (len sur ecran projete / 2) + 1.
ca c'est notre taille totale. Avec cette taille et cam distscreen on recup la valeur de l'angle.
- 90 degres - cet angle represente l'angle dans le triangle inverse. Avec cet angle du triangle
inverse on peut calculer le cote oppose qui correspond au ray_len qui va toucher notre texture
(car on a le cote adjacent qui est la hauteur a laquelle evolue la camera qui est definie comme
size_wall / 2).
- on determine ensuite les coordonnees xi et yi de l'intersection du rayon
- Une fois qu'on a l'endroite ou on touche la texture, il faut aller chercher dans son image le
bon pixel grace a une fonction qui convertit ces coordonnes
*/

/*
** Using coordinates of intersection point to determinate which color of the
** floor texture we have to print. Looking for the pixel at the line y and
** row x.
*/
int		find_color_case_sky(t_mlx *mlx, t_point i)
{
	int		color;
	int		line;
	int		row;

	i.x = fabs(i.x - ((double)(int)i.x));
	i.y = fabs(i.y - ((double)(int)i.y));
	row = (int)(i.x * (double)WALL_SIZE); //texture should be size of texture walls (64 x 64, defined)
	line = (int)(i.y * (double)WALL_SIZE);
	color = mlx->addr->t_so[row + line * mlx->info->t_so[SIZE_LINE]];
	return (color);
}

/*
** Launches a ray for each pixel on screen below the projected wall to the
** floor, and determinates where it hits the map. First calculating the angle
** of tri rect between : cam dist screen, projected wall + a number of pixel
** floors (depending on which ray we're launching). Then evolves in the
** opposite tri rect (cam height (adj), ray crossing floor (hypothenuse), 
** distance len on the map between cam and inter pont (opp, = flo_ray_len).
** Return the correct color of the floor's pixel texture.
*/
int		sky_raycasting(t_mlx *mlx, double height, double rcast_angle)
{
	double	angle;
	double	flo_ray_len;	//distance on the map between cam and inter point
	t_point	i;				//intersection point with ray_floor on the map

	angle = atan(height / mlx->cam->dist_screen) * TO_DEG;
	angle = 90.0 - angle; //evolving in the inverse triangle
	flo_ray_len = (tan(angle * TO_RAD) * ((double)WALL_SIZE / 2.0))
				/ (double)WALL_SIZE; //also converting len in pixels to normal unity on the map
	flo_ray_len /= cos(fabs(mlx->cam->angle - rcast_angle) * TO_RAD); //correcting fisheye in the opposite sens
	angle = angle_tri_rect(rcast_angle); //convert angle between 0 and 90 degrees for trigo calculations
	i.x = flo_ray_len * cos(angle * TO_RAD); //looking for adj, using hypothenuse and angle (trigo)
	i.y = flo_ray_len * sin(angle * TO_RAD); //looking for opp, using hypothenuse and angle (trigo)
	if (rcast_angle > 0.0 && rcast_angle < 180.0)	//if ray going up
		i.y *= -1.0;
	if (rcast_angle > 90.0 && rcast_angle < 270.0)	//if ray going left
		i.x *= -1.0;
	i.x += mlx->cam->x; //finding intersection point from player position
	i.y += mlx->cam->y;
	return (find_color_case_sky(mlx, i));
}

/*
** Using coordinates of intersection point to determinate which color of the
** floor texture we have to print. Looking for the pixel at the line y and
** row x.
*/
int		find_color_case_floor(t_mlx *mlx, t_point i)
{
	int		color;
	int		line;
	int		row;

	i.x = fabs(i.x - ((double)(int)i.x));
	i.y = fabs(i.y - ((double)(int)i.y));
	row = (int)(i.x * (double)WALL_SIZE); //texture should be size of texture walls (64 x 64, defined)
	line = (int)(i.y * (double)WALL_SIZE);
	color = mlx->addr->t_ea[row + line * mlx->info->t_ea[SIZE_LINE]];
	return (color);
}

/*
** Launches a ray for each pixel on screen below the projected wall to the
** floor, and determinates where it hits the map. First calculating the angle
** of tri rect between : cam dist screen, projected wall + a number of pixel
** floors (depending on which ray we're launching). Then evolves in the
** opposite tri rect (cam height (adj), ray crossing floor (hypothenuse), 
** distance len on the map between cam and inter pont (opp, = flo_ray_len).
** Return the correct color of the floor's pixel texture.
*/
int		floor_raycasting(t_mlx *mlx, double height, double rcast_angle)
{
	double	angle;
	double	flo_ray_len;	//distance on the map between cam and inter point
	t_point	i;				//intersection point with ray_floor on the map

	angle = atan(height / mlx->cam->dist_screen) * TO_DEG;
	angle = 90.0 - angle; //evolving in the inverse triangle
	flo_ray_len = (tan(angle * TO_RAD) * ((double)WALL_SIZE / 2.0))
				/ (double)WALL_SIZE; //also converting len in pixels to normal unity on the map
	flo_ray_len /= cos(fabs(mlx->cam->angle - rcast_angle) * TO_RAD); //correcting fisheye in the opposite sens
	angle = angle_tri_rect(rcast_angle); //convert angle between 0 and 90 degrees for trigo calculations
	i.x = flo_ray_len * cos(angle * TO_RAD); //looking for adj, using hypothenuse and angle (trigo)
	i.y = flo_ray_len * sin(angle * TO_RAD); //looking for opp, using hypothenuse and angle (trigo)
	if (rcast_angle > 0.0 && rcast_angle < 180.0)	//if ray going up
		i.y *= -1.0;
	if (rcast_angle > 90.0 && rcast_angle < 270.0)	//if ray going left
		i.x *= -1.0;
	i.x += mlx->cam->x; //finding intersection point from player position
	i.y += mlx->cam->y;
	return (find_color_case_floor(mlx, i));
}
