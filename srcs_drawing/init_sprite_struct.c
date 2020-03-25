/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 16:40:35 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/25 10:58:44 by lucaslefran      ###   ########.fr       */
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
	int		inv_color;

	inv_color = 0;
	type == SP_TREE ? inv_color = 9961608 : 0;
	type == SP_ARMOR ? inv_color = 9961608 : 0;
	type == SP_HEALTH ? inv_color = 9961608 : 0;
	type == SP_LAMP ? inv_color = 9961608 : 0;
	type == SP_SPEARS ? inv_color = 9961608 : 0;
	type == SP_FLAG ? inv_color = 9961608 : 0;
	return (inv_color);
}

/*
** Return the memory address of sprite image depending on spri_num.
*/
int		*add_sprite_img_addr(t_mlx *mlx, int type)
{
	int		*addr_sprite;

	addr_sprite = NULL;
	type == SP_TREE ? addr_sprite = mlx->addr->s_4 : 0;
	type == SP_ARMOR ? addr_sprite = mlx->addr->s_5 : 0;
	type == SP_HEALTH ? addr_sprite = mlx->addr->s_6 : 0;
	type == SP_LAMP ? addr_sprite = mlx->addr->s_7 : 0;
	type == SP_SPEARS ? addr_sprite = mlx->addr->s_8 : 0;
	type == SP_FLAG ? addr_sprite = mlx->addr->s_9 : 0;
	return (addr_sprite);
}

/*
** Return the width of one sprite on screen in pixel. Ex : tree sprite is
** taking half of the xpm img (with a witdh of 64 pixels), so tree size is 32
** pixels.
*/
int		sprite_size(int type)
{
	int		size;

	size = 0;
	type == SP_TREE ? size = TREE_SIZE : 0;
	type == SP_ARMOR ? size = ARMOR_SIZE : 0;
	type == SP_HEALTH ? size = HEALTH_SIZE : 0;
	type == SP_LAMP ? size = LAMP_SIZE : 0;
	type == SP_SPEARS ? size = SPEARS_SIZE : 0;
	type == SP_FLAG ? size = FLAG_SIZE : 0;
	return (size);
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
	new->size = sprite_size(new->type);
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
