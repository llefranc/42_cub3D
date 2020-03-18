/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 13:40:24 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/18 16:23:20 by lucaslefran      ###   ########.fr       */
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
double	ray_len(double xa, double ya, double xb, double yb)
{
	return (sqrt(pow(xb - xa, 2.0) + pow(yb - ya, 2.0))); //√((xb - xa)² + (yb - ya)²)
}

/*
** Use Thales theoreme to determinate height of 1 object projected on the
** screen, and return the number of pixels that need to be colored.
** All objects must be size of the walls (defined).
** distance cam_projection_screen / distance cam_obj == height obj_on_screen / height wall_in_game
*/
double	height_object(t_rcast *cam, double ray_len)
{
	double	h_object;
	double	dist_cam_obj_ing;

	dist_cam_obj_ing = ray_len * (double)WALL_SIZE; //one case of the map (x = 1 or y = 1) == WALL_SIZE
	h_object = ((double)WALL_SIZE / dist_cam_obj_ing) * (cam->dist_screen);
	return (h_object);
}

/*
** Return the row of img texture that will be needed later to fill the wall on
** screen, by determinating which row of the wall is touched (with a size of 64)
** is touched by the ray. Also determinate which side of the wall is touched by
** the row (NORTH, SOUTH, EAST, WEST).
*/
int		nb_image_row(t_rcast *cam, t_texture *textu, double xa, double ya)
{
	int		row_img;	//if ray touch NORTH or SOUTH -> y_len = 0 || x_len = 0 for EAST and WEST
	double	x_len;		//x_len is the len of the portion touched by ray on 'x axe'
	double	y_len;		//y_len is the len of the portion touched by ray on 'y axe'

	x_len = cam->x + xa - (double)((int)(cam->x + xa));
	y_len = cam->y + ya - (double)((int)(cam->y + ya));
	if ((x_len > y_len && x_len < 0.9999999) || y_len > 0.99) //y_len > 0.99 handle a strange case where y_len should value 0 but
	{													 	  //it's taking 0.9999999... value due to round errors
		row_img = (int)(x_len * (double)WALL_SIZE);
		textu->side_wall = (textu->angle_raycast >= 0.0 && textu->angle_raycast < 180.0) ? NORTH : SOUTH;
	}
	else
	{
		row_img = (int)(y_len * (double)WALL_SIZE); //if y_len == 0.33 >> we will print the row number (WALL_SIZE / 3)
		textu->side_wall = (textu->angle_raycast >= 90.0 && textu->angle_raycast < 270.0) ? EAST : WEST;
	}
	return (row_img);
}

/*
** Compare the len of 2 rays :
** x_ray, stopping when it meets a wall and checking each time it crosses 'y axe')
** y_ray, stopping when it meets a wall and checking each time it crosses 'x axe')
** Then using the smaller one to determinate in pixel the size of the wall on the
** screen. Also determinate which row of texture img we will use to fill the wall
** on screen.
*/
double		nb_pixel_wall(t_mlx *mlx, t_rcast *cam, t_texture *textu, double angle)
{
	double	h_wall; //size of the wall on the screen in pixels
	double	x_ray;
	double	y_ray;

	textu->angle_raycast = angle; //needed in nb_image_row func
	x_ray = x_ray_len(mlx, cam, angle, textu) * cos(fabs(cam->angle - angle) * TO_RAD); //correcting fisheye with pythagore
	y_ray = y_ray_len(mlx, cam, angle, textu) * cos(fabs(cam->angle - angle) * TO_RAD);
	if (y_ray != y_ray || x_ray <= y_ray)	//y_ray != y_ray handle the case of y_ray = NAN, can be true only if y_ray is NAN
	{										//Compare something with NAN will always be false.
		textu->row_img = nb_image_row(cam, textu, textu->x_xa, textu->x_ya);
		h_wall = height_object(cam, x_ray);
	}
	else									//If x_ray is NAN, x_ray <= y_ray will be false
	{										
		textu->row_img = nb_image_row(cam, textu, textu->y_xa, textu->y_ya);
		h_wall = height_object(cam, y_ray);
	}
	return (h_wall);
}
