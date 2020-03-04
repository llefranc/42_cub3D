/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:40:24 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/04 12:04:54 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** if the angle is negative, will add k * 360 degrees until the angle is
** included between 0 and 360 degrees. If positive, will substract k * 360.
*/
double	positive_angle(double angle)
{
	while (angle < 0.0)
		angle += 360.0;
	while (angle >= 360.0)
		angle -= 360.0;
	return (angle);
}

/*
** Tranform the actual angle of the ray between 0 and 90 degrees because we have
** for trigonometry calculation.
*/
double	angle_tri_rect(double angle)
{
	if (angle < 0.0)
	{
		while (angle < 0.0)
			angle += 360.0;
		return (angle_tri_rect(angle));
	}
	else if (angle > 360.0)
	{
		while (angle > 360.0)
			angle -= 360.0;
		return (angle_tri_rect(angle));
	}
	else if (angle >= 0.0 && angle <= 90.0)
		return (angle);
	else if (angle > 90.0 && angle <= 180.0)
		return (180.0 - angle);
	else if (angle > 180.0 && angle <= 270.0)
		return (angle - 180.0);
	else
		return (360.0 - angle);
}

/*
** Use pythagore to calculate the len of a ray (distance between two coordinates).
*/
double	ray_len(t_rcast *cam, double x_len, double y_len)
{
	x_len = cam->x + x_len;
	y_len = cam->y + y_len;
	return (sqrt(pow(x_len - cam->x, 2.0) + pow(y_len - cam->y, 2.0))); //√((xb - xa)² + (yb - ya)²)
}

/*
** Use Thales theoreme to determinate height of the wall projected on the
** screen, and return the number of pixels that need to be colored.
** distance cam_screen / distance cam_wall == hegiht wall_on_screen / height wall_in_game
*/
double	height_wall(t_rcast *cam, double ray_len)
{
	double	h_wall;
	double	dist_cam_wall_ing;

	dist_cam_wall_ing = ray_len * (double)WALL_SIZE; //one case of the map == WALL_SIZE
	h_wall = ((double)WALL_SIZE / dist_cam_wall_ing) * cam->dist_screen;

	//verifier pourquoi mettre wall_size car il s'annule dans l'equation. pourtant si je change la hauteur du mur,
	//cela ne devrait pas rendre pareil sur l'ecran de projection en theorie ? bien garder en tete que la camera est
	//fixee au milieu du mur donc elle si on change auteur du mur ca grandit notre personnage. Mais le mur devriat quand
	//meme en theorie ressortir plus grand sur l'ecran de projection non ?
	return (h_wall);
}

/*
** Compare the len of 2 rays :
** x_ray, stopping when it meets a wall and checking each time it crosses 'y axe')
** y_ray, stopping when it meets a wall and checking each time it crosses 'x axe')
** Then using the smaller one to determinate in pixel the size of the wall on the
** screen.
*/
int		nb_pixel_wall(t_rcast *cam, double angle)
{
	double	h_wall;
	double	x_ray;
	double	y_ray;

	x_ray = x_ray_len(cam, angle) * cos(fabs(cam->angle - angle) * TO_RAD); //correcting fisheye with pythagore and cos
	y_ray = y_ray_len(cam, angle) * cos(fabs(cam->angle - angle) * TO_RAD);
	if (y_ray != y_ray || x_ray <= y_ray)	//y_ray != y_ray handle the case of y_ray == NAN. 
		h_wall = height_wall(cam, x_ray);	//Compare something with NAN will always be false.
	else									//y_ray != y_ray can be true only if y_ray is NAN.
		h_wall = height_wall(cam, y_ray);	//If x_ray is NAN, x_ray <= y_ray will be false
	return ((int)h_wall);
}
