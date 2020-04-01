/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_ennemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 11:16:55 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/01 17:13:47 by lucaslefran      ###   ########.fr       */
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
** Return -1 if it's out of the map. Return 2 if a guard sprite.
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
	if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == SP_GUARD) //if a guard
		return (2);
	if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == 1 || //if wall
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == DOOR ||
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == SECRETDOOR)
		return (0);
	return (1); //if empty or opened door / secretdoor
}

/*
** Return 0 if it finds a wall/door for a certain position in the map.
** Return -1 if it's out of the map. Return 2 if a guard sprite.
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
	if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == SP_GUARD) //if a guard
		return (2);
	if (mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == 1 || //if wall
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == DOOR ||
			mlx->cam->map[(int)(mlx->cam->y + y_len)][(int)(mlx->cam->x + x_len)] == SECRETDOOR)
		return (0);
	return (1); //if empty or opened door / secretdoor 
}

/*
** Checking x values on 'x axe' each time the ray cross 'y axe' until it meets
** a wall or exit the map. Return the len of the ray on 'x axe', depending on
** the angle. If angle == 0 or 180 degrees, nan will be returned (ray will 
** never cross 'y axe').
*/
double	x_ray_len_wall(t_mlx *mlx, t_rcast *cam, double angle)
{
	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
	double	ya; //next crosses on x = y1 + nb * ya, with ya the distance between
				// each line of y s(so 1 or -1 depending on the angle)
	double	xa; //next crosses on y = x1 + nb * xa, xa is the distance between x1 and
				//the next cross of y axe
	
	if (angle <= 0.0 || angle >= 360.0 || angle == 180.0) //we will never cross 'y axe'
		return (NAN);
	y1 = x_ray_y1_value(cam, angle); //cam->y + y1 => border of the actual square (y axe)
	ya = x_ray_ya_value(angle); 
	x1 = x_ray_x1_value(angle, y1); //cam->x + x1 => border of the actual square (x axe)
	xa = x_ray_xa_value(angle, y1, ya) - x1;
	while (x_ray_find_len_wall(mlx, angle, x1, y1) > 0) //until we find a wall/door or exit map
	{
		x1 += xa; //next cross with y axe 
		y1 += ya; //moving of (+-)1 unity on 'y axe'
	}
	return (ray_len(cam->x, cam->y, cam->x + x1, cam->y + y1)); //len of ray when we cross 'x axe' and meet a wall
}

/*
** Checking y values on 'y axe' each time the ray cross 'x axe' until it meets a
** a wall or exit the map. Return the len of the ray on 'y axe', depending on
** the angle. If angle == 90 or 270 degrees, nan will be returned (ray will 
** never cross 'x axe').
*/
double	y_ray_len_wall(t_mlx *mlx, t_rcast *cam, double angle)
{
	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
	double	xa; //next crosses on y = x1 + nb * xa, with xa the distance between
				// each line of x (so 1 or -1 depending on the angle)
	double	ya; //next crosses on x = y1 + nb * ya, ya is the distance between x1 and
				//the next cross of 'y axe'

	if (angle == 90.0 || angle == 270.0) //we will never cross 'x axe'
		return (NAN);
	x1 = y_ray_x1_value(cam, angle); //cam->x + x1 => border of the actual square (x axe)
	xa = y_ray_xa_value(angle);
	y1 = y_ray_y1_value(angle, x1); //cam->y + y1 => border of the actual square (y axe)
	ya = y_ray_ya_value(angle, x1, xa) - y1;
	while (y_ray_find_len_wall(mlx, angle, x1, y1) > 0) //until we find a wall/door or exit map
	{
		x1 += xa; //moving of (+-)1 unity on 'x axe'
		y1 += ya; //next cross with 'x axe'
	}
	return (ray_len(cam->x, cam->y, cam->x + x1, cam->y + y1)); //len of ray when we cross 'y axe' and we meet a wall
}

/*
** Find a ray between the player and the guard sprites. Compare the len of this
** ray to the len of the ray between player and wall. If ray guard < ray wall,
** then the wall is behind the guard and the guard can see the player, and his
** status is set to DETECTING_PLAYER (defined), otherwise to NOT_SEEING. If
** it's the first time the guard is detecting the player, the function starts
** a timer for the guard detecting animation.
*/
void	check_guard_detect_player(t_mlx *mlx, t_rcast *cam, t_sprites *spri)
{
	double	angle;
	double	x_ray;
	double	y_ray;
	int		wasnt_seeing; //to save if the guard was previously detecting or not the player

	if (spri->guard.status >= DYING) //if the guard is dead
		return ;
	wasnt_seeing = spri->guard.status; //if guard wasnt seeing the player, will value 0
	spri->guard.status = NOT_SEEING;
	angle = find_angle(cam, spri);
	x_ray = x_ray_len_wall(mlx, cam, angle);
	y_ray = y_ray_len_wall(mlx, cam, angle);
	//y_ray != y_ray handle the case of y_ray = NAN, can be true only if y_ray is NAN. 
	//Compare something with NAN will always be false.
	if (y_ray != y_ray || x_ray <= y_ray)
		ray_len(cam->x, cam->y, spri->x, spri->y) < x_ray ? spri->guard.status = DETECTING_PLAYER : 0;
	else if (ray_len(cam->x, cam->y, spri->x, spri->y) < y_ray) //if ray between player and guard < ray between player and wall
		spri->guard.status = DETECTING_PLAYER;
	if (!wasnt_seeing && spri->guard.status == DETECTING_PLAYER)	//if the guard has just started to detect the player
		gettimeofday(&spri->guard.time_detect, NULL);				//we initiate the timer
}
