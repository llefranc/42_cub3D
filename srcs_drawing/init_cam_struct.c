/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:34:54 by llefranc          #+#    #+#             */
/*   Updated: 2020/04/01 17:32:47 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Read the map and search for the player position in order to initiate his
** starting position and angle of view. Also save number of max rows for each
** line.
*/
void	init_player_pos(t_mlx *mlx, t_rcast *cam)
{
	int		line;
	int		row;

	line = 0;
	while (cam->map[line]) //map is terminated by a NULL *ptr
	{
		row = 0;
		while (cam->map[line][row] != -2)
		{
			if (cam->map[line][row] >= 10) //player position
			{
				cam->x = (double)row + 0.5;		//adding 0.5 so the player will start
				cam->y = (double)line + 0.5;	//in the middle of the square
				cam->map[line][row] == EAST ? cam->angle = V_EAST : 0; //0 degees
				cam->map[line][row] == NORTH ? cam->angle = V_NORTH : 0; //90 degrees
				cam->map[line][row] == WEST ? cam->angle = V_WEST : 0; //180 degrees
				cam->map[line][row] == SOUTH ? cam->angle = V_SOUTH : 0; //270 degrees
				cam->map[line][row] = 0;
			}
			else if (cam->map[line][row] > 3) //if it's a sprite
				add_sprite_info(mlx, cam, line, row); //creating and filling new sprite struct
			row++;
		}
		cam->nb_rows[line] = row; //save number max of rows for each line
		line++;
	}
}

void	struct_init_cam_bool(t_rcast *cam)
{
	cam->m_up = 0;		//booleans for movements
	cam->m_down = 0;
	cam->m_left = 0;
	cam->m_right = 0;
	cam->r_left = 0;	//booleans for rotations
	cam->r_right = 0;
	cam->rm_left = 0;
	cam->rm_right = 0;
	cam->mouse_bool = 0; //first use of the mouse
	cam->mouse_x = 0;	 //x position of the mouse
}

/*
** Fill structure cam with the following parameters :
** Number of lines / rows in the map, player position (x, y), angle of view for
** the camera. Also saves all the information about sprites.
*/
void	struct_init_camera(t_mlx *mlx, t_rcast *cam, t_pars *par)
{
	int		line;

	line = 0;
	struct_init_cam_bool(cam);
	while (par->map[line]) //counting number of lines
		line++;
	cam->nb_lines = line;
	if (!(cam->nb_rows = malloc(line * sizeof(int)))) //for nb rows max for each line
		error_msg_destroy_img("Malloc failed\n", mlx);
	cam->map = par->map;
	init_player_pos(mlx, cam); //save player position + number of max rows for each line + sprites info
	cam->dist_screen = (par->reso[0] / 2.0) / tan(((double)FOV / 2.0) * (TO_RAD)); //pythagore, 
	cam->freq_ray = (double)FOV / par->reso[0];
	cam->par = par;	//allow to only carry t_rcast struct
	mlx->eve.start_angle = cam->angle;	//saving start player's information in the case
	mlx->eve.start_pos_x = cam->x;		//he has to respawn
	mlx->eve.start_pos_y = cam->y;
}
