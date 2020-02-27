/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:40:24 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/27 17:17:53 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Tranform the actual angle of the ray between 0 and 90 degrees because we have
** for trigonometry calculation.
*/
double	angle_tri_rect(double angle)
{
	if (angle >= 0.0 && angle <= 90.0)
		return (angle);
	else if (angle > 90.0 && angle <= 180.0)
		return (180.0 - angle);
	else if (angle > 180.0 && angle <= 270.0)
		return (angle - 180.0);
	else
		return (360.0 - angle);
}

/*
** Return 1 if it finds a wall for a certain position in the map, 0 otherwise.
** Return -1 if it's out of the map. Corrects the position in the map because
** we're evolving in a tab[y][x]:
** for angle > 0 && < 180 : tab[y - 1][x] (checking if there's a wall above us)
** for angle > 90 && < 270 : tab[y][x - 1] (checking if there's a wall at our left).
*/
int		find_wall(t_rcast *cam, double angle, double x_len, double y_len)
{
	if (angle > 0.0 && angle < 180.0)
		y_len -= 1.0; //at the intersection with y axe, checking if wall above us
	else if (angle > 90.0 && angle < 270.0)
		x_len -= 1.0; //at the intersection with y axe, checking if wall at our left
	if ((int)(cam->y + y_len) < 0 || (int)(cam->y + y_len) >= cam->nb_lines //if we're out of the map
		|| (int)(cam->x + x_len) < 0 || (int)(cam->x + x_len) >= cam->nb_rows)
		return (-1);
	if (cam->map[(int)(cam->y + y_len)][(int)(cam->x + x_len)] != 1) //if not a wall
		return (0);
	return (1); //only if we find a wall
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
** screen. The value will be >= 0 && <= WALL_SIZE (defined).
*/
double	height_wall(t_rcast *cam, double ray_len)
{
	double	h_wall;
	double	dist_cam_wall_ing;

	dist_cam_wall_ing = cam->dist_screen + ray_len * (double)WALL_SIZE;
	h_wall = WALL_SIZE * (cam->dist_screen / dist_cam_wall_ing);
	return (h_wall);
}

/*
** Compare the len of 2 rays :
** x_ray, stopping when it meets a wall and checking each time it crosses 'y axe')
** y_ray, stopping when it meets a wall and checking each time it crosses 'x axe')
** Then using the smaller one to determinate in pixel the size of the wall on the
** screen.
*/
int		nb_pixel_wall(t_pars *par, t_rcast *cam, double angle)
{
	double	h_wall; //will be between 0 and SIZE_WALL (defined)
	double	x_ray;
	double	y_ray;
	int		nb_pixel;

	x_ray = x_ray_len(cam, angle) * cos(fabs(cam->angle - angle) * TO_RAD); //correcting fisheye with pythagore and cos
	y_ray = y_ray_len(cam, angle) * cos(fabs(cam->angle - angle) * TO_RAD);
	if (y_ray != y_ray || x_ray <= y_ray)	//y_ray != y_ray handle the case of y_ray == NAN. 
		h_wall = height_wall(cam, x_ray);	//Compare something with NAN will always be false.
	else									//y_ray != y_ray can be true only if y_ray is NAN.
		h_wall = height_wall(cam, y_ray);	//If x_ray is NAN, x_ray <= y_ray will be false
	nb_pixel = (int)(par->reso[1] * (double)WALL_SIZE / h_wall); //doing a ratio of resolution y
	return (nb_pixel);
}
