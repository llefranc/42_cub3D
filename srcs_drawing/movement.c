/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:04:03 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/23 14:19:34 by lucaslefran      ###   ########.fr       */
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
	double	tmp_len;

	tmp_len = (len > 0.0) ? len + 0.1 : len - 0.1; //to prevent player to be to close to walls
	if (coordinate == 'x') //allow to use this fucntion for 'x' or 'y'
	{
		if ((int)(cam->x + tmp_len) < 0 || (int)(cam->x + tmp_len) >= cam->nb_rows[(int)cam->y]) //if we're out of the map 
			return ;
		if (cam->map[(int)(cam->y)][(int)(cam->x + tmp_len)] == 1) //if a wall
			return ;
		cam->x += len;
	}
	else if (coordinate == 'y')
	{
		if ((int)(cam->y + tmp_len) < 0 || (int)(cam->y + tmp_len) >= cam->nb_lines) //if we're out of the map
			return ;
		if (cam->map[(int)(cam->y + tmp_len)][(int)(cam->x)] == 1) //if a wall
			return ;
		cam->y += len;
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going up.
*/
void	move_up_in_map(t_mlx *mlx, double move_size)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going down.
*/
void	move_down_in_map(t_mlx *mlx, double move_size)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else
	{
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going left.
*/
void	move_left_in_map(t_mlx *mlx, double move_size)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, +sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, +cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else
	{
		move(mlx->cam, +sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
}

/*
** Using trigonometry to determinate new player's coordinates when he's going right.
*/
void	move_right_in_map(t_mlx *mlx, double move_size)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		move(mlx->cam, sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
	else
	{
		move(mlx->cam, -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'x');
		move(mlx->cam, cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * move_size, 'y');
	}
}

/*
** Calculates the time between two frames when a movement key is pressed, and
** adjusts the size of the movement so player's movement are not slowed when
** the framerate is dropping (with huge resolution for exemple).
*/
void	move_accords_framerate(t_mlx *mlx, double move)
{
	double			time;
	struct timeval	end;

	gettimeofday(&end, NULL);
	time = (double)(end.tv_usec - mlx->start_move.tv_usec) / 1000000.0 +
         (double)(end.tv_sec - mlx->start_move.tv_sec);
	if (mlx->start_move.tv_sec != 0.0) //if the key wasn't just pressed
		move *= time / TIME_MOVE;
	mlx->cam->m_up ? move_up_in_map(mlx, move) : 0;
	mlx->cam->m_down ? move_down_in_map(mlx, move) : 0;
	mlx->cam->m_left ? move_left_in_map(mlx, move) : 0;
	mlx->cam->m_right ? move_right_in_map(mlx, move) : 0;
	gettimeofday(&mlx->start_move, NULL); //setting start here for the next rotation
}

/*
** Calculates the time between two frames when a rotation key is pressed, and
** adjusts the size of the rotation so player's rotation is not slowed when
** the framerate is dropping (with huge resolution for exemple).
*/
void	rota_accords_framerate(t_mlx *mlx, double rota)
{
	double			time;
	struct timeval	end;

	gettimeofday(&end, NULL);
	time = (double)(end.tv_usec - mlx->start_rota.tv_usec) / 1000000.0 +
         (double)(end.tv_sec - mlx->start_rota.tv_sec);
	if (mlx->start_rota.tv_sec != 0.0) //if the key wasn't just pressed
		rota *= time / TIME_MOVE;
	mlx->cam->r_left ? mlx->cam->angle = positive_angle(mlx->cam->angle + rota) : 0; //rotation
	mlx->cam->r_right ? mlx->cam->angle = positive_angle(mlx->cam->angle - rota) : 0;
	gettimeofday(&mlx->start_rota, NULL); //setting start here for the next rotation
}
