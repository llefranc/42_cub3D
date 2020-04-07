/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_sky_raycast.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 17:54:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/06 14:46:00 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Calculates for each pixel above walls its height on the screen (ratio), and
** its position on a 360 angle. Then access the skybox img at the correct line
** and row.
*/
int		draw_skybox(t_mlx *mlx, double height, double rcast_angle)
{
	int		row;
	int		line;
	int		color;

	height = mlx->par->reso[1] - height;
	line = (int)((height / (mlx->par->reso[1] / 2.0)) //reso / 2 because sky could be at max half of the screen
			* (double)(mlx->info.t_sk[HEIGHT] - 1));
	row = (int)(rcast_angle / 360.0 * (double)mlx->info.t_sk[WIDTH]);
	color = mlx->addr.t_sk[row + line * mlx->info.t_sk[SIZE_LINE]];
	return (color);
}

/*
** Using coordinates of intersection point to determinate which color of the
** floor texture we have to print. Looking for the pixel at the line y and
** row x.
*/
int		find_color_square_floor(t_mlx *mlx, t_point i)
{
	int		color;
	int		line;
	int		row;

	i.x = fabs(i.x - ((double)(int)i.x));
	i.y = fabs(i.y - ((double)(int)i.y));
	row = (int)(i.x * (double)WALL_SIZE); //texture should be size of texture walls (64 x 64, defined)
	line = (int)(i.y * (double)WALL_SIZE);
	color = mlx->addr.t_fl[row + T_FLOOR_R + line * mlx->info.t_fl[SIZE_LINE]
			+ T_FLOOR_L * mlx->info.t_fl[SIZE_LINE]];
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
	return (find_color_square_floor(mlx, i));
}
