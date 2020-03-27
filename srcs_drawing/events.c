/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:44:38 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/26 10:46:46 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Allow to rotate when the player is moving the mouse.
*/
int		motion_notify(int x, int y, t_mlx *mlx)
{
	unsigned int	x_tmp;

	(void)y;
	if (mlx->cam->mouse_bool == 1) //at the moment the mouse is activated, to initiate it
	{
		mlx->cam->mouse_bool = 2;
		mlx->cam->mouse_x = x;	//we're saving original position of the mouse
	}
	if (mlx->cam->mouse_bool) 
	{
		x_tmp = abs(x - mlx->cam->mouse_x); //usefull for acceleration
		if (x_tmp > 9)		//to lower too huge acceleration
			x_tmp = (int)sqrt((double)x_tmp) * 3;
		if (x < mlx->cam->mouse_x) //allow to know if the mouse is moving left or right
			mlx->cam->rm_left = M_ROTA_SIZE * x_tmp;
		else if (x > mlx->cam->mouse_x)
			mlx->cam->rm_right = M_ROTA_SIZE * x_tmp;
		mlx->cam->mouse_x = x;		//for the next moove with the mouse
	}
	return (1);
}

/*
** Control player's movements. When a key is pressed, the boolean is set to 1
** and the function for this movement will start to be called until the player
** released the key.
*/
int		key_press(int keycode, t_mlx *mlx)
{
	if (keycode == W_KEY) //movements
		mlx->cam->m_up = 1;
	else if (keycode == S_KEY)
		mlx->cam->m_down = 1;
	else if (keycode == A_KEY)
		mlx->cam->m_left = 1;
	else if (keycode == D_KEY)
		mlx->cam->m_right = 1;
	else if (keycode == LEFT_KEY) //rotation
		mlx->cam->r_left = 1;
	else if (keycode == RIGHT_KEY)
		mlx->cam->r_right = 1;
	else if (keycode == M_KEY) 	//activating or desactivating the rotation with the mouse
		mlx->cam->mouse_bool = (mlx->cam->mouse_bool == 0) ? 1 : 0;
	else if (keycode == T_KEY)	//activating or desactivating texture printing for sky and floor
		mlx->eve.print_texture = (mlx->eve.print_texture == 0) ? 1 : 0;
	else if (keycode == E_KEY) //open a door if close to one
		open_door(mlx);
	else if (keycode == ESC_KEY)	//free and exit
	{
		struct_free(mlx->par);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

/*
** Control player's movements. When a key is released, the boolean is set to 0
** and the function for this movement will stop to be called.
*/
int		key_release(int keycode, t_mlx *mlx)
{
	if (keycode == W_KEY)	//movements
		mlx->cam->m_up = 0;
	if (keycode == S_KEY)
		mlx->cam->m_down = 0;
	if (keycode == A_KEY)
		mlx->cam->m_left = 0;
	if (keycode == D_KEY)
		mlx->cam->m_right = 0;
	if (keycode == LEFT_KEY)	//rotation
		mlx->cam->r_left = 0;
	if (keycode == RIGHT_KEY)
		mlx->cam->r_right = 0;
	return (1);
}

/*
** Allow to properly qui the program when the player is closing the window.
*/
int		destroy_notify(t_mlx *mlx)
{
	struct_free(mlx->par);
	free_sprite_struct(mlx->spri);
	destroy_all_images(mlx, &mlx->img);
	exit(EXIT_SUCCESS);
}

/*
** Moove the player's position if some movements were activated in keypress
** and keyrelease, rotates the camera, then actualize the screen by doing the raycasting. 
*/
int		no_event(t_mlx *mlx)
{
	//update player position
	if (((mlx->cam->m_up || mlx->cam->m_down) && (mlx->cam->m_left || mlx->cam->m_right))
			&& (!(mlx->cam->m_up && mlx->cam->m_down) && !(mlx->cam->m_left && mlx->cam->m_right)))
		move_accords_framerate(mlx, MOVE_SIZE / 2.0); //so player doesn't move 2x faster when 2 keys are pressed
	else if (mlx->cam->m_up || mlx->cam->m_down || mlx->cam->m_left || mlx->cam->m_right)
		move_accords_framerate(mlx, MOVE_SIZE);
	else
		mlx->start_move.tv_sec = 0.0;
	//update camera rotation
	if (mlx->cam->r_left || mlx->cam->r_right)
		rota_accords_framerate(mlx, ROTA_SIZE);
	else
		mlx->start_rota.tv_sec = 0.0;
	mlx->cam->rm_left ? mlx->cam->angle = positive_angle(mlx->cam->angle + mlx->cam->rm_left) : 0;
	mlx->cam->rm_right ? mlx->cam->angle = positive_angle(mlx->cam->angle - mlx->cam->rm_right) : 0;
	raycasting(mlx);
	draw_hud_anims(mlx, mlx->par, &mlx->info);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img.screen, 0, 0);
	mlx->cam->rm_left = 0.0;
	mlx->cam->rm_right = 0.0;
	return (1);
}
