/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:10:26 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/24 11:21:04 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Calculates the two coordinates of one point depending of an angle by using
** trigonometry, and by starting the calculs from the middle of the square.
*/
void	calc_coordinates(double angle, t_sprites *spri, char c)
{
	double	x_len;
	double	y_len;
	double	ratio;		//ratio between sprite's width on screen and full width of sprite img
	double	tmp_angle;

	tmp_angle = angle_tri_rect(angle);
	x_len = 0.5 * cos(tmp_angle * TO_RAD);	//we're evolving in a trigo environnement
	y_len = 0.5 * sin(tmp_angle * TO_RAD);	//and we know that its ray is 0.5
	ratio = (double)spri->size / (double)WALL_SIZE;
	if (angle > 0.0 && angle < 180.0)
		y_len *= -1.0;
	if (angle > 90.0 && angle < 270.0)
		x_len *= -1.0;
	if (c == 'A')	//first point, filling xa and ya
	{
		spri->a.x = (double)spri->x + 0.5 + x_len;
		spri->a.y = (double)spri->y + 0.5 + y_len;
		spri->a_sized.x = (double)spri->x + 0.5 + x_len * ratio; //for sprite collision
		spri->a_sized.y = (double)spri->y + 0.5 + y_len * ratio;
	}
	else			//second point, filling xb and yb
	{
		spri->b.x = (double)spri->x + 0.5 + x_len;
		spri->b.y = (double)spri->y + 0.5 + y_len;
		spri->b_sized.x = (double)spri->x + 0.5 + x_len * ratio; //for sprite collision
		spri->b_sized.y = (double)spri->y + 0.5 + y_len * ratio;
	}
}

/*
** Determinates for each sprite the orientation of sprite's plan depending on
** the camera's angle. Calculates two points, A and B, representing a segment
** with a len of 1.
*/
void	calc_sprites_orientation(t_sprites **spri, double angle)
{
	int		i;

	i = -1;
	if (!spri) //if no sprite
		return ;
	while (spri[++i])	//creating new plan for each sprites
	{
		calc_coordinates(positive_angle(angle + 90.0), spri[i], 'A');	//creating a line with 90 degrees angle
		calc_coordinates(positive_angle(angle - 90.0), spri[i], 'B');	//with cam orientation, so we can evolve in
	}																	//trigo environment
}

/*
** Reset all ray lens for sprites at each tour of loop.
*/
void	reset_ray_len_sprites(t_sprites **spri)
{
	int		i;

	i = -1;
	if (!spri) //if no sprite
		return ;
	while (spri[++i])
	{
		spri[i]->ray_len = -1.0;
		spri[i]->nb_pix = -1.0;
		spri[i]->row_percent = -1.0;
		spri[i]->freq_pixel = -1.0;
		spri[i]->start_line_img = -1;
	}
}

/*
** Search in a tab of sprites struct the *ptr sprites that will correspond to
** the x and y coordinates send in arg. Return NULL if no *ptr sprites correspond.
** Corrects the position in the map because we're evolving in a tab[y][x]:
** if angle > 0 && < 180 : tab[y - 1][x] (checking if there's a sprite above us)
*/
t_sprites	*sprites_ptr_x_ray(t_mlx *mlx, double angle, double x1, double y1)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	if (angle > 0.0 && angle < 180.0)
		y1 = (double)((int)(y1)) - 1.0; //at the intersection with y axe, checking if sprite above us
	else if (mlx->cam->y + y1 - (double)((int)(mlx->cam->y + y1)) > 0.99)
		y1 = (double)((int)(y1)) + 1.0; //for an exception due to round error
	x = (int)(mlx->cam->x + x1);
	y = (int)(mlx->cam->y + y1);
	while (mlx->spri && mlx->spri[i] && (mlx->spri[i]->y != y || mlx->spri[i]->x != x))
		i++;									//looking for sprite of x and y coordinates
	if (!mlx->spri)	//in case of no sprites in the map
		return (NULL);
	return (mlx->spri[i]);
}

/*
** Search in a tab of sprites struct the *ptr sprites that will correspond to
** the x and y coordinates send in arg. Return NULL if no *ptr sprites correspond.
** Corrects the position in the map because we're evolving in a tab[y][x]:
** for angle > 90 && < 270 : tab[y][x - 1] (checking if there's a sprite at our left).
*/
t_sprites	*sprites_ptr_y_ray(t_mlx *mlx, double angle, double x1, double y1)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	if (angle > 90.0 && angle < 270.0)
		x1 = (double)((int)(x1)) - 1.0; //at the intersection with y axe, checking if sprite at our left
	else if (mlx->cam->x + x1 - (double)((int)(mlx->cam->x + x1)) > 0.99)
		x1 = (double)((int)(x1)) + 1.0; //for an exception due to round error
	x = (int)(mlx->cam->x + x1);
	y = (int)(mlx->cam->y + y1);
	while (mlx->spri && mlx->spri[i] && (mlx->spri[i]->y != y || mlx->spri[i]->x != x))
		i++;									//looking for sprite of x and y coordinates
	if (!mlx->spri)	//in case of no sprites in the map
		return (NULL);
	return (mlx->spri[i]);
}

/*
** Determinates if 2 segments (AB, the sprite's plan, and CD, the ray launched)
** are crossing each other. If it's the case, calculates the len of the ray and
** the portion of the sprites touched by the ray (to print the correct row of
** the image).
*/
void	find_sprites(t_mlx *mlx, t_sprites *spri, double xd, double yd, double angle)
{
	t_point c;
	t_point	p;		//instersection point
	t_point vec_i;	//represent AB segment
	t_point vec_j;	//represent CD segment
	double	k;		//len of AB line when it's crossing CD, should be < 1.0 if it occurs on segment AB
	double	m;		//len of CD line when it's crossing AB, same

	if (!spri || spri->ray_len != -1.0)	//in y_ray algo, meeting a sprite that was already treated
		return ;						//in x_ray algo, or in the case there isn't any sprite in the map
	c.x = mlx->cam->x;
	c.y = mlx->cam->y;
	vec_i.x = spri->b.x - spri->a.x;	//coordinates of i vector
	vec_i.y = spri->b.y - spri->a.y;
	vec_j.x = xd - c.x;					//coordinates of j vector
	vec_j.y = yd - c.y;
	m = -(-vec_i.x * spri->a.y + vec_i.x * c.y + vec_i.y * spri->a.x - vec_i.y * c.x) 
			/ (vec_i.x * vec_j.y - vec_i.y * vec_j.x);
	k = -(spri->a.x * vec_j.y - c.x * vec_j.y - vec_j.x * spri->a.y + vec_j.x * c.y)
			/ (vec_i.x * vec_j.y - vec_i.y * vec_j.x);
	if (m > 0.0 && m < 1.0 && k > 0.0 && k < 1.0) //segment AB and CD are crossing each other
	{
		p.x = spri->a.x + k * vec_i.x;	//determinating intersection point coordinates
		p.y = spri->a.y + k * vec_i.y;
		spri->ray_len = ray_len(c.x, c.y, p.x, p.y);
		spri->ray_len *= cos(fabs(mlx->cam->angle - angle) * TO_RAD);	//correcting fisheye with pythagore
		spri->row_percent = ray_len(spri->a.x, spri->a.y, p.x, p.y);	//portion of the sprite that is
	}																	//touched by the ray
}
