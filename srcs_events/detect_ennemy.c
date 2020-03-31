/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_ennemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 13:49:39 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/31 15:06:58 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Return value of the angle made by a ray (between the player and the guard)
** in a trigonometric environnement (360 degrees).
*/
double	find_angle(t_rcast *cam, t_sprites *spri)
{
	double	x_len;
	double	y_len;
	double	angle;

	x_len = fabs(spri->x - cam->x); //evolving in rectangle triange
	y_len = fabs(spri->y - cam->y);
	angle = atan(y_len / x_len) * TO_DEG;
	if (spri->x <= cam->x && spri->y <= cam->y)	//translating angle from a rectangle triangle (90 degrees)
		angle = 180.0 - angle;					//into trigo environnement (360 degrees) (player point of view)
	else if (spri->x <= cam->x && spri->y >= cam->y)
		angle = 180.0 + angle;
	else if (spri->x >= cam->x && spri->y > cam->y)
		angle = 360.0 - angle;
	return (angle);
}

/*
** Return 0 if it finds a wall/door for a certain position in the map.
** Return -1 if it's out of the map. Return 2 if a sprite.
** Corrects the position in the map because we're evolving in a tab[y][x]:
** if angle > 0 && < 180 : tab[y - 1][x] (checking if there's a wall above us)
*/
int		x_ray_find_len_wall(t_mlx *mlx, double angle, double x_len, double y_len)
{
	if ((x_len || y_len) && (angle > 0.0 && angle < 180.0)) //!x1 && !y1 when player is standing on a sprite' square
		y_len = (double)((int)(y_len)) - 1.0; //at the intersection with y axe, checking if wall above us
	else if (mlx->cam->y + y_len - (double)((int)(mlx->cam->y + y_len)) > 0.99)
		y_len = (double)((int)(y_len)) + 1.0;
	if ((int)(mlx->cam->y + y_len) < 0 || (int)(mlx->cam->y + y_len) >= mlx->cam->nb_lines) //if we're out of the map (lines)
		return (-1);
	if ((int)(mlx->cam->x + x_len) < 0 || (int)(mlx->cam->x + x_len) >= 
			mlx->cam->nb_rows[(int)(mlx->cam->y + y_len)]) //same for rows
		return (-1);
	if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] > 3 &&
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] < 10) //if a sprite
		return (2);
	else if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == 0 || //if empty
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == DOOR + 10 || //if door opened (we're not printing it)
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == SECRETDOOR + 10)
		return (1);
	return (0);
}

/*
** Return 0 if it finds a wall/door for a certain position in the map.
** Return -1 if it's out of the map. Return 2 if a sprite.
** Corrects the position in the map because we're evolving in a tab[y][x]:
** for angle > 90 && < 270 : tab[y][x - 1] (checking if there's a wall at our left).
*/
int		y_ray_find_len_wall(t_mlx *mlx, double angle, double x_len, double y_len)
{
	if ((x_len || y_len) && (angle > 90.0 && angle < 270.0)) //!x1 && !y1 when player is standing on a sprite' square
		x_len = (double)((int)(x_len)) - 1.0; //at the intersection with y axe, checking if wall at our left
	else if (mlx->cam->x + x_len - (double)((int)(mlx->cam->x + x_len)) > 0.99)
		x_len = (double)((int)(x_len)) + 1.0;
	if ((int)(mlx->cam->y + y_len) < 0 || (int)(mlx->cam->y + y_len) >= mlx->cam->nb_lines) //if we're out of the map (lines)
		return (-1);
	if ((int)(mlx->cam->x + x_len) < 0 || (int)(mlx->cam->x + x_len) >=
			mlx->cam->nb_rows[(int)(mlx->cam->y + y_len)]) //same for rows
		return (-1);
	if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] > 3 &&
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] < 10) //if a sprite
		return (2);
	else if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == 0 || //if empty
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == DOOR + 10 || //if door opened (we're not printing it)
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == SECRETDOOR + 10)
		return (1);
	return (0); //only if we find a wall or doors
}

/*
** Checking x values on 'x axe' each time the ray cross 'y axe' until it meets a
** a wall or exit the map. Return the len of the ray on 'x axe', depending on
** the angle. If angle == 0 or 180 degrees, inf will be returned (ray will 
** never cross 'y axe'). If 1 is send in detect, will also change the value of
** status to 1 when the ray meets a guard sprite.
*/
double	x_ray_ennemy_seeing(t_mlx *mlx, t_rcast *cam, double angle, int detect)
{
	int		ret;
	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
	double	ya; //next crosses on x = y1 + nb * ya, with ya the distance between
				// each line of y s(so 1 or -1 depending on the angle)
	double	xa; //next crosses on y = x1 + nb * xa, xa is the distance between x1 and
				//the next cross of y axe
	
	if (angle <= 0.0 || angle >= 360.0 || angle == 180.0) //we will never cross 'y axe'
		return (INFINITY);
	y1 = x_ray_y1_value(cam, angle); //cam->y + y1 => border of the actual square (y axe)
	ya = x_ray_ya_value(angle); 
	x1 = x_ray_x1_value(angle, y1); //cam->x + x1 => border of the actual square (x axe)
	xa = x_ray_xa_value(angle, y1, ya) - x1;
	//in the case player is standing on a sprite' square, the ray met a guard and detect == 1 to indicate
	//we're allowed to change value of guard status parameter
	if (x_ray_find_wall(mlx, angle, 0, 0) == 2 && detect && sprites_ptr_x_ray(mlx, angle, 0, 0)->type == SP_GUARD)
		sprites_ptr_x_ray(mlx, angle, 0, 0)->guard.status = DETECTING_PLAYER;
	while ((ret = x_ray_find_len_wall(mlx, angle, x1, y1)) > 0) //until we find a wall/door or exit map
	{
		if (ret == 2 && detect && sprites_ptr_x_ray(mlx, angle, x1, y1)->type == SP_GUARD) //same than just above
			sprites_ptr_x_ray(mlx, angle, x1, y1)->guard.status = DETECTING_PLAYER;
		x1 += xa; //next cross with y axe 
		y1 += ya; //moving of (+-)1 unity on 'y axe'
	}
	return (ray_len(cam->x, cam->y, cam->x + x1, cam->y + y1)); //len of ray when we cross 'x axe' and meet a wall
}

/*
** Checking y values on 'y axe' each time the ray cross 'x axe' until it meets a
** a wall or exit the map. Return the len of the ray on 'y axe', depending on
** the angle. If angle == 90 or 270 degrees, nan will be returned (ray will 
** never cross 'x axe'). If 1 is send in detect, will also change the value of
** status to 1 when the ray meets a guard sprite.
*/
double	y_ray_ennemy_seeing(t_mlx *mlx, t_rcast *cam, double angle, int detect)
{
	int		ret;
	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
	double	xa; //next crosses on y = x1 + nb * xa, with xa the distance between
				// each line of x (so 1 or -1 depending on the angle)
	double	ya; //next crosses on x = y1 + nb * ya, ya is the distance between x1 and
				//the next cross of 'y axe'

	if (angle == 90.0 || angle == 270.0) //we will never cross 'x axe'
		return (100000.0);
	x1 = y_ray_x1_value(cam, angle); //cam->x + x1 => border of the actual square (x axe)
	xa = y_ray_xa_value(angle);
	y1 = y_ray_y1_value(angle, x1); //cam->y + y1 => border of the actual square (y axe)
	ya = y_ray_ya_value(angle, x1, xa) - y1;
	//in the case player is standing on a sprite' square, the ray met a guard and detect == 1 to indicate
	//we're allowed to change value of guard status parameter
	if (y_ray_find_wall(mlx, angle, 0, 0) == 2 && detect && sprites_ptr_y_ray(mlx, angle, 0, 0)->type == SP_GUARD)
		sprites_ptr_y_ray(mlx, angle, 0, 0)->guard.status = DETECTING_PLAYER;
	while ((ret = y_ray_find_len_wall(mlx, angle, x1, y1)) > 0) //until we find a wall/door or exit map
	{
		if (ret == 2 && detect && sprites_ptr_y_ray(mlx, angle, x1, y1)->type == SP_GUARD) //same than just above
			sprites_ptr_y_ray(mlx, angle, x1, y1)->guard.status = DETECTING_PLAYER;
		x1 += xa; //moving of (+-)1 unity on 'x axe'
		y1 += ya; //next cross with 'x axe'
	}
	return (ray_len(cam->x, cam->y, cam->x + x1, cam->y + y1)); //len of ray when we cross 'y axe' and we meet a wall
}

/*
** Calculates the angle between player and spri (== guard sprite), and lauch a
** ray with this angle. Each time the ray will detect a guard sprite, it will
** change the status value to 1. If the guard was previously not detecting
** the player and just started now, it also initializes one timer to print
** guard's animations when he's first seeing the player.
*/
void	check_guard_detect_player(t_mlx *mlx, t_rcast *cam, t_sprites *spri)
{
	double	angle;
	int		wasnt_seeing;

	if (spri->guard.status >= DYING) //if the guard is dead
		return ;
	wasnt_seeing = spri->guard.status; //if guard wasnt seeing the player, will value 0
	spri->guard.status = NOT_SEEING;
	angle = find_angle(cam, spri); //angle made by ray in trigo env with player and guard (player point of view)
	//detecting which ray will first reach a wall (sending 0 to not change guard parameters, just focusing on ray len)
	if (x_ray_ennemy_seeing(mlx, cam, angle, 0) <= y_ray_ennemy_seeing(mlx, cam, angle, 0))
		x_ray_ennemy_seeing(mlx, cam, angle, 1); //sending 1 to change guard parameter (if he's seeing player or not)
	else
		y_ray_ennemy_seeing(mlx, cam, angle, 1);
	if (!wasnt_seeing && spri->guard.status == DETECTING_PLAYER)	//if the guard has just started to detect the player
		gettimeofday(&spri->guard.time_detect, NULL);				//we initiate the timer
}
