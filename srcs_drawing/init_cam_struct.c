/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:34:54 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/23 11:23:51 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Free a double tab of sprites structures.
*/
void	free_sprite_struct(t_sprites **spri)
{
	int		i;

	i = 0;
	while (spri[i])
		free(spri[i++]);
	free(spri);
}

/*
** Create a new tab of *sprites and a new one at the end, and then NULL
** terminate the tab. Free the previous tab of *sprites.
*/
void	add_sprite_struct(t_mlx *mlx, t_sprites *new)
{
	int			i;
	t_sprites	**tmp;
	
	i = 0;
	if (!mlx->spri) //if it's the first sprite in our sprites'tab
	{
		if (!(mlx->spri = malloc(sizeof(*tmp) * 2))) //+2 for new sprite and NULL terminating
			error_msg_destroy_img("Malloc failed\n", mlx);
		mlx->spri[0] = new;
		mlx->spri[1] = NULL;
	}
	else
	{
		tmp = mlx->spri;
		while (mlx->spri[i])
			i++;
		if (!(mlx->spri = malloc(sizeof(*tmp) * (i + 2)))) //+2 for new sprite and NULL terminating
		{
			free_sprite_struct(mlx->spri);
			error_msg_destroy_img("Malloc failed\n", mlx);
		}
		mlx->spri[i] = new;
		mlx->spri[i + 1] = NULL;
		while (--i >= 0) //we copy the previous **sprites in the new one
			mlx->spri[i] = tmp[i];
		free(tmp);
	}
}

/*
** Return depending on the type the background color (in a int) that we will
** not print.
*/
int		sprites_background_color(int type)
{
	if (type == 2)
		return (9961608);
	return (1);
}

/*
** Return the memory address of sprite image depending on spri_num.
*/
int		*add_sprite_img_addr(t_mlx *mlx, int spri_num)
{
	if (spri_num == 2)
		return (mlx->addr->s_2);
	return (NULL);
}

/*
** Create and intialize a new sprite struct, and then call a function to add
** it at the end of a double tab of sprite struct.
*/
void	add_sprite_info(t_mlx *mlx, t_rcast *cam, int line, int row)
{
	t_sprites	*new;

	if (!(new = malloc(sizeof(*new))))
	{
		free_sprite_struct(mlx->spri);
		error_msg_destroy_img("Malloc failed\n", mlx);
	}
	new->type = cam->map[line][row];
	new->addr_img = add_sprite_img_addr(mlx, new->type);
	new->inv_color = sprites_background_color(new->type);
	new->x = row;
	new->y = line;
	new->ray_len = -1.0;
	new->start_line_img = -1;
	new->freq_pixel = -1.0;
	new->nb_pix = -1.0;
	new->row_percent = -1.0;
	new->a.x = -1.0;
	new->a.y = -1.0;
	new->b.x = -1.0;
	new->b.y = -1.0;
	add_sprite_struct(mlx, new);
}

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
				cam->y = (double)line + 0.5;	//in the middle of the case
				cam->map[line][row] == EAST ? cam->angle = V_EAST : 0; //0 degees
				cam->map[line][row] == NORTH ? cam->angle = V_NORTH : 0; //90 degrees
				cam->map[line][row] == WEST ? cam->angle = V_WEST : 0; //180 degrees
				cam->map[line][row] == SOUTH ? cam->angle = V_SOUTH : 0; //270 degrees
				cam->map[line][row] = 0;
			}
			else if (cam->map[line][row] > 1) //if it's a sprite
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
}
