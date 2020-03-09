/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:56:38 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 12:01:50 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Return the distance on 'y axe' before it meets the border of the actual case,
** depending on ray angle value.
*/
double	x_ray_y1_value(t_rcast *cam, double angle)
{
	double	y1;
	double	y_round;

	y1 = cam->y;
	y_round = round(y1); //if y1 < 3.5 y_round = 3.0 || y >= 3.5 y_round = 4.0
	if (y_round > y1) //y1 >= 3.5
	{
		if (angle > 0.0 && angle < 180.0)
			y1 = -1.0 + (y_round - y1); //y1 neg, we're going up in the tab
		else if (angle > 180.0 && angle < 360.0)
			y1 = y_round - y1; //y1 pos, we're going down in the tab
	}
	else if (y_round < y1) //y1 < 3.5
	{
		if (angle > 0.0 && angle < 180.0)
			y1 = y_round - y1;
		else if (angle > 180.0 && angle < 360.0)
			y1 = 1.0 - (y1 - y_round);
	}
	else //y1 = 3.0
		y1 = 0.0;
	return (y1);
}

/*
** Return the value of ya for h_ray equation depending on the ray angle.
** Return -1 for angle > 0 && angle < 180, 1 for angle > 180 and angle < 360,
** 0 for angle == 0 || angle == 180.
*/
double	x_ray_ya_value(double angle)
{
	if (angle > 0 && angle < 180) //we're going up in the tab so ya is negative
		return (-1.0);
	else if (angle > 180 && angle < 360) //we're going down in the tab so ya is positive
		return (1.0);
	else //horizontal ray will never cross 'y axe'
		return (0.0);
}

/*
** Return x1 value (len x before corresponding from our position to first
** intersection with 'y axe') depending on the angle. x1 will be neg if angle
** is between 90 and 270 degrees.
*/
double	x_ray_x1_value(double angle, double y1)
{
	double x1;

	if (y1 < 0.0) //we need pos values for trigo calculation
		y1 *= -1.0;
	x1 = y1 / tan(angle_tri_rect(angle) * TO_RAD);
	if (angle > 90.0 && angle <= 270.0)
		x1 *= -1.0;
	return (x1);
}

/*
** Return xa value (len xa between x1 and the next intersection with 'y axe', if
** we move on 1 unity on 'y axe' and depending on the ray angle. xa will be neg
** for an angle between 90 and 270 degrees.
*/
double	x_ray_xa_value(double angle, double y1, double ya)
{
	double xa;

	if (y1 < 0.0) //we need pos values for trigo calculation
		y1 *= -1.0;
	if (ya < 0.0)
		ya *= -1.0;
	y1 += ya;
	xa = y1 / tan(angle_tri_rect(angle) * TO_RAD);
	if (angle > 90.0 && angle <= 270.0)
		xa *= -1.0;
	return (xa);
}

/*
** Return 1 if it finds a wall for a certain position in the map, 0 otherwise.
** Return -1 if it's out of the map. Corrects the position in the map because
** we're evolving in a tab[y][x]:
** if angle > 0 && < 180 : tab[y - 1][x] (checking if there's a wall above us)
*/
int		x_ray_find_wall(t_rcast *cam, double angle, double x_len, double y_len)
{
	if (angle > 0.0 && angle < 180.0)
		y_len = (double)((int)y_len) - 1.0; //at the intersection with y axe, checking if wall above us
	if ((int)(cam->y + y_len) < 0 || (int)(cam->y + y_len) >= cam->nb_lines) //if we're out of the map (lines)
		return (-1);
	if ((int)(cam->x + x_len) < 0 || (int)(cam->x + x_len) >= cam->nb_rows[(int)(cam->y + y_len)]) //same for rows
		return (-1);
	if (cam->map[(int)(cam->y + y_len)][(int)(cam->x + x_len)] != 1) //if not a wall
		return (0);
	return (1); //only if we find a wall
}

/*
** Checking x values on 'x axe' each time the ray cross 'y axe' until it meets a
** a wall or exit the map. Return the len of the ray on 'x axe', depending on
** the angle. If angle == 0 or 180 degrees, nan will be returned (ray will 
** never cross 'y axe'). If angle == 90 or 270 degrees, 0 will be returned (ray
** go up or down but doesn't move on 'x axe').
*/
double	x_ray_len(t_rcast *cam, double angle)
{
	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
	double	ya; //next crosses on x = y1 + nb * ya, with ya the distance between
				// each line of y s(so 1 or -1 depending on the angle)
	double	xa; //next crosses on y = x1 + nb * xa, xa is the distance between x1 and
				//the next cross of y axe
	
	if (angle <= 0.0 || angle >= 360.0 || angle == 180.0) //we will never cross 'y axe'
		return (NAN);
	y1 = x_ray_y1_value(cam, angle); //cam->y + y1 => border of the actual case (y axe)
	ya = x_ray_ya_value(angle); 
	x1 = x_ray_x1_value(angle, y1); //cam->x + x1 => border of the actual case (x axe)
	xa = x_ray_xa_value(angle, y1, ya) - x1;
	while (!x_ray_find_wall(cam, angle, x1, y1)) //until we find a wall or exit map
	{
		x1 += xa; //next cross with y axe 
		y1 += ya; //moving of (+-)1 unity on 'y axe'
	}
	return (ray_len(cam, x1, y1)); //len of ray when we cross 'x axe' and meet a wall
}
