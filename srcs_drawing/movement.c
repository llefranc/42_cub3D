/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:04:03 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 12:22:15 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Check if by adding len to one of the player's coordinates, the movement is ok
** (means the player is neither out of the map, neither in a wall). If it's good,
** add len to the player's coordinate ('x' or 'y'). Handling collisions just
** with walls. Otherwise do nothing (for example with sprites). 
*/
void	move(t_rcast *cam, double len, char coordinate)
{
	if (coordinate == 'x') //allow to use this fucntion for 'x' or 'y'
	{
		if ((int)(cam->x + len) < 0 || (int)(cam->x + len) >= cam->nb_rows[(int)cam->y]) //if we're out of the map 
			return ;
		if (cam->map[(int)(cam->y)][(int)(cam->x + len)] == 1) //if a wall
			return ;
		cam->x += len;
	}
	else if (coordinate == 'y')
	{
		if ((int)(cam->y + len) < 0 || (int)(cam->y + len) >= cam->nb_lines) //if we're out of the map
			return ;
		if (cam->map[(int)(cam->y + len)][(int)(cam->x)] == 1) //if a wall
			return ;
		cam->y += len;
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going up.
*/
void	move_up_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going down.
*/
void	move_down_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going left.
*/
void	move_left_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, +sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, +cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else
	{
		move(mlx->cam, +sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going right.
*/
void	move_right_in_map(t_mlx *mlx)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
	else
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'x');
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * MOVE_SIZE, 'y');
	}
}