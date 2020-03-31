/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 14:52:42 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/31 14:47:36 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Using trigonometry to determinate new point's coordinates with a certain len.
*/
void	add_len_to_ray(t_mlx *mlx, t_point *square, double size_len)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		square->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		square->x += -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		square->x += -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
	else
	{
		square->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
}

/*
** When a certain key is pressed, launch a ray with a len of 1.0 in the
** direction of cam->angle and check every 0.1 unity if it encounters a door or
** a secret door. If it's the case, add 10 to the door' square to indicate it's
** now open (walls raycasting will not print it now). If interaction with a
** door opened, it removes 10 to indicate it's closed and door is printed again.
*/
void	open_door(t_mlx *mlx)
{
	int		i;
	t_point	square;

	i = -1;
	square.x = mlx->cam->x; //we start from player position
	square.y = mlx->cam->y;
	while (++i < 10) //checking every 0.1 unity
	{
		add_len_to_ray(mlx, &square, 0.1);
		if (mlx->cam->map[(int)square.y][(int)square.x] == DOOR || //if door or secret door
				mlx->cam->map[(int)square.y][(int)square.x] == SECRETDOOR)
		{
			mlx->cam->map[(int)square.y][(int)square.x] +=10; //add 10 to not print in and consider door open
			return ;
		}
		else if ((mlx->cam->map[(int)square.y][(int)square.x] == DOOR + 10	//if open door or open secret door
				|| mlx->cam->map[(int)square.y][(int)square.x] == SECRETDOOR + 10)
				&& mlx->cam->map[(int)mlx->cam->y][(int)mlx->cam->x] != 	//to prevent to close door on player position
				mlx->cam->map[(int)square.y][(int)square.x])
		{
			mlx->cam->map[(int)square.y][(int)square.x] -=10; //door is now closed
			return ;
		}
	}
}

int		set_ennemy_to_death_value(t_sprites *spri)
{
	if (spri->guard.status >= DYING)
		return (0);
	spri->guard.status = DYING;
	gettimeofday(&spri->guard.time_death, NULL);
	return (1);
}

//A MODIFIER
/*
** Checking x values on 'x axe' each time the ray cross 'y axe' until it meets a
** a wall or exit the map. Return the len of the ray on 'x axe', depending on
** the angle. If angle == 0 or 180 degrees, inf will be returned (ray will 
** never cross 'y axe'). If 1 is send in detect, will also change the value of
** see_player to 1 when the ray meets a guard sprite.
*/
int		x_ray_shooting_ennemy(t_mlx *mlx, t_rcast *cam, double angle)
{
	int		ret;
	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
	double	ya; //next crosses on x = y1 + nb * ya, with ya the distance between
				// each line of y s(so 1 or -1 depending on the angle)
	double	xa; //next crosses on y = x1 + nb * xa, xa is the distance between x1 and
				//the next cross of y axe
	
	if (angle <= 0.0 || angle >= 360.0 || angle == 180.0) //we will never cross 'y axe'
		return (-1);
	y1 = x_ray_y1_value(cam, angle); //cam->y + y1 => border of the actual square (y axe)
	ya = x_ray_ya_value(angle); 
	x1 = x_ray_x1_value(angle, y1); //cam->x + x1 => border of the actual square (x axe)
	xa = x_ray_xa_value(angle, y1, ya) - x1;
	//in the case player is standing on a sprite' square, the ray met a guard and detect == 1 to indicate
	//we're allowed to change value of guard see_player parameter
	if (x_ray_find_len_wall(mlx, angle, 0, 0) == 2 && sprites_ptr_x_ray(mlx, angle, 0, 0)->type == SP_GUARD)
		if (set_ennemy_to_death_value(sprites_ptr_x_ray(mlx, angle, 0, 0)))
			return (1);
	while ((ret = x_ray_find_len_wall(mlx, angle, x1, y1)) > 0) //until we find a wall/door or exit map
	{
		if (ret == 2 && sprites_ptr_x_ray(mlx, angle, x1, y1)->type == SP_GUARD) //same than just above
			if (set_ennemy_to_death_value(sprites_ptr_x_ray(mlx, angle, x1, y1)))
				return (1);
		x1 += xa; //next cross with y axe 
		y1 += ya; //moving of (+-)1 unity on 'y axe'
	}
	return (0);
}

//A MODIFIER
/*
** Checking y values on 'y axe' each time the ray cross 'x axe' until it meets a
** a wall or exit the map. Return the len of the ray on 'y axe', depending on
** the angle. If angle == 90 or 270 degrees, nan will be returned (ray will 
** never cross 'x axe'). If 1 is send in detect, will also change the value of
** see_player to 1 when the ray meets a guard sprite.
*/
int		y_ray_shooting_ennemy(t_mlx *mlx, t_rcast *cam, double angle)
{
	int		ret;
	double	x1; //distance on 'x axe' when we first cross 'y axe' with a certain angle
	double	y1; //distance on 'y axe' when we first cross 'x axe' with a certain angle
	double	xa; //next crosses on y = x1 + nb * xa, with xa the distance between
				// each line of x (so 1 or -1 depending on the angle)
	double	ya; //next crosses on x = y1 + nb * ya, ya is the distance between x1 and
				//the next cross of 'y axe'

	if (angle == 90.0 || angle == 270.0) //we will never cross 'x axe'
		return (-1);
	x1 = y_ray_x1_value(cam, angle); //cam->x + x1 => border of the actual square (x axe)
	xa = y_ray_xa_value(angle);
	y1 = y_ray_y1_value(angle, x1); //cam->y + y1 => border of the actual square (y axe)
	ya = y_ray_ya_value(angle, x1, xa) - y1;
	//in the case player is standing on a sprite' square, the ray met a guard and detect == 1 to indicate
	//we're allowed to change value of guard see_player parameter
	if (y_ray_find_len_wall(mlx, angle, 0, 0) == 2 && sprites_ptr_y_ray(mlx, angle, 0, 0)->type == SP_GUARD)
		if (set_ennemy_to_death_value(sprites_ptr_y_ray(mlx, angle, 0, 0)))
			return (1);
	while ((ret = y_ray_find_len_wall(mlx, angle, x1, y1)) > 0) //until we find a wall/door or exit map
	{
		if (ret == 2 && sprites_ptr_y_ray(mlx, angle, x1, y1)->type == SP_GUARD) //same than just above
			if (set_ennemy_to_death_value(sprites_ptr_y_ray(mlx, angle, x1, y1)))
				return (1);
		x1 += xa; //moving of (+-)1 unity on 'x axe'
		y1 += ya; //next cross with 'x axe'
	}
	return (0);
}

/*
** Starts the timer for the shooting animation.
*/
void	shoot_anim(t_mlx *mlx)
{
	mlx->eve.gun_shot = 1;
	(mlx->eve.ammo)--;
	if (x_ray_ennemy_seeing(mlx, mlx->cam, mlx->cam->angle, 0) <=
			y_ray_ennemy_seeing(mlx, mlx->cam, mlx->cam->angle, 0))
		x_ray_shooting_ennemy(mlx, mlx->cam, mlx->cam->angle);
	else
		y_ray_shooting_ennemy(mlx, mlx->cam, mlx->cam->angle);
	gettimeofday(&mlx->eve.gun_time_start, NULL);
}
