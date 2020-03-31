/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 11:16:55 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/31 14:26:10 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

// /*
// ** Return value of the angle made by a ray (between the player and the guard)
// ** in a trigonometric environnement (360 degrees).
// */
// double	find_angle(t_rcast *cam, t_sprites *spri)
// {
// 	double	x_len;
// 	double	y_len;
// 	double	angle;

// 	x_len = fabs(spri->x - cam->x); //evolving in rectangle triange
// 	y_len = fabs(spri->y - cam->y);
// 	angle = atan(y_len / x_len) * TO_DEG;
// 	if (spri->x <= cam->x && spri->y <= cam->y)	//translating angle from a rectangle triangle (90 degrees)
// 		angle = 180.0 - angle;					//into trigo environnement (360 degrees) (player point of view)
// 	else if (spri->x <= cam->x && spri->y >= cam->y)
// 		angle = 180.0 + angle;
// 	else if (spri->x >= cam->x && spri->y > cam->y)
// 		angle = 360.0 - angle;
// 	return (angle);
// }

// int		x_ray_find_len_wall(t_mlx *mlx, double angle, double x_len, double y_len)
// {
// 	if ((x_len || y_len) && (angle > 0.0 && angle < 180.0)) //!x1 && !y1 when player is standing on a sprite' square
// 		y_len = (double)((int)(y_len)) - 1.0; //at the intersection with y axe, checking if wall above us
// 	else if (mlx->cam->y + y_len - (double)((int)(mlx->cam->y + y_len)) > 0.99)
// 		y_len = (double)((int)(y_len)) + 1.0;
// 	if ((int)(mlx->cam->y + y_len) < 0 || (int)(mlx->cam->y + y_len) >= mlx->cam->nb_lines) //if we're out of the map (lines)
// 		return (-1);
// 	if ((int)(mlx->cam->x + x_len) < 0 || (int)(mlx->cam->x + x_len) >= 
// 			mlx->cam->nb_rows[(int)(mlx->cam->y + y_len)]) //same for rows
// 		return (-1);
// 	if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] > 3 &&
// 			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] < 10) //if a sprite
// 		return (2);
// 	else if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == 0 || //if empty
// 			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == DOOR + 10 || //if door opened (we're not printing it)
// 			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == SECRETDOOR + 10)
// 		return (1);
// 	return (0);
// }

// double	x_ray_len_wall(t_mlx *mlx, t_rcast *cam, double angle)
// {
// 	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
// 	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
// 	double	ya; //next crosses on x = y1 + nb * ya, with ya the distance between
// 				// each line of y s(so 1 or -1 depending on the angle)
// 	double	xa; //next crosses on y = x1 + nb * xa, xa is the distance between x1 and
// 				//the next cross of y axe
	
// 	if (angle <= 0.0 || angle >= 360.0 || angle == 180.0) //we will never cross 'y axe'
// 		return (NAN);
// 	y1 = x_ray_y1_value(cam, angle); //cam->y + y1 => border of the actual square (y axe)
// 	ya = x_ray_ya_value(angle); 
// 	x1 = x_ray_x1_value(angle, y1); //cam->x + x1 => border of the actual square (x axe)
// 	xa = x_ray_xa_value(angle, y1, ya) - x1;
// 	while (x_ray_find_len_wall(mlx, angle, x1, y1) > 0) //until we find a wall/door or exit map
// 	{
// 		x1 += xa; //next cross with y axe 
// 		y1 += ya; //moving of (+-)1 unity on 'y axe'
// 	}
// 	return (ray_len(cam->x, cam->y, cam->x + x1, cam->y + y1)); //len of ray when we cross 'x axe' and meet a wall
// }


// double	y_ray_len_wall(t_mlx *mlx, t_rcast *cam, double angle)
// {
// 	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
// 	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
// 	double	xa; //next crosses on y = x1 + nb * xa, with xa the distance between
// 				// each line of x (so 1 or -1 depending on the angle)
// 	double	ya; //next crosses on x = y1 + nb * ya, ya is the distance between x1 and
// 				//the next cross of 'y axe'

// 	if (angle == 90.0 || angle == 270.0) //we will never cross 'x axe'
// 		return (NAN);
// 	x1 = y_ray_x1_value(cam, angle); //cam->x + x1 => border of the actual square (x axe)
// 	xa = y_ray_xa_value(angle);
// 	y1 = y_ray_y1_value(angle, x1); //cam->y + y1 => border of the actual square (y axe)
// 	ya = y_ray_ya_value(angle, x1, xa) - y1;
// 	while (y_ray_find_wall(mlx, angle, x1, y1) > 0) //until we find a wall/door or exit map
// 	{
// 		x1 += xa; //moving of (+-)1 unity on 'x axe'
// 		y1 += ya; //next cross with 'x axe'
// 	}
// 	return (ray_len(cam->x, cam->y, cam->x + x1, cam->y + y1)); //len of ray when we cross 'y axe' and we meet a wall
// }

// void	check_guard_detect_player(t_mlx *mlx, t_rcast *cam, t_sprites *spri)
// {
// 	double	angle = 187.629590321959227594561525620520114898681640625;
// 	double	x_ray;
// 	double	y_ray;
// 	t_texture textu;

// 	printf("CHECK	: DEB, adresse spri = %p\n", spri);
// 	// angle = find_angle(cam, spri);
// 	printf("CHECK	: angle = %.60f\n", angle);
// 	printf("cam->x = %.2f, cam->y = %.60f\n", cam->x, cam->y);
// 	x_ray = x_ray_len(mlx, cam, angle, &textu);
// 	// printf("CHECK	: x_raycasting = %f\n", x_ray);
// 	// x_ray = x_ray_len_wall(mlx, cam, angle);
// 	printf("CHECK	: x_ray = %f\n", x_ray);
// 	y_ray = y_ray_len(mlx, cam, angle, &textu);
// 	// printf("CHECK	: y_raycasting = %f\n", y_ray);
// 	// y_ray = y_ray_len_wall(mlx, cam, angle);
// 	printf("CHECK	: y_ray = %f\n", y_ray);
// 	printf("CHECK	: FIN, adresse spri = %p\n\n", spri);
// }

// void	guards_seeing_player(t_mlx *mlx, t_rcast *cam, t_sprites **spri)
// {
// 	int		i;

// 	i = -1;
// 	while (spri[++i])
// 	{
// 		if (spri[i]->type == SP_GUARD)
// 		{
// 			check_guard_detect_player(mlx, cam, spri[i]);
// 			// printf("DETECT : %d\n", spri[i]->guard.status);
// 		}
// 	}
// }
