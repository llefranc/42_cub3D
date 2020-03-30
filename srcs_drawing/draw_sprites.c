/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 19:08:04 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/29 14:10:32 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Swaps two *ptr of struct sprites.
*/
void	swap_sprites(t_sprites **sprite1, t_sprites **sprite2)
{
	t_sprites	*tmp;

	tmp = *sprite1;
	*sprite1 = *sprite2;
	*sprite2 = tmp;
}

/*
** Sorts a tab of sprites from the biggest ray_len to the smallest one.
*/
void	sort_sprites_tab(t_sprites **spri)
{
	int			i;
	int			j;

	i = 0;
	while (spri && spri[i] && spri[i + 1])
	{
		j = i;
		while (spri[++j])
			if (spri[i]->ray_len < spri[j]->ray_len)
				swap_sprites(&spri[i], &spri[j]);
		i++;
	}
}

/*
** Allow to resize the sprite by calculating at which frequence each pixel
** has to be print. Sprites have a size of 64 pixels.
** Exemple : if pix_spri value 192, each 3 screen's pixels will have the color
** of 1 sprite's pixel.
*/
void	sprite_resizing(t_mlx *mlx, t_sprites *spri, double *pix_spri)
{
	int		pix_spri2;
	int		no_limit_pix_spri;

	no_limit_pix_spri = (int)*pix_spri;
	*pix_spri > mlx->par->reso[1] ? *pix_spri = mlx->par->reso[1] : 0; //if nb colored pixel walls > resolution
	pix_spri2 = (int)*pix_spri;
	if (pix_spri2 >= no_limit_pix_spri) //the whole sprite will fit in the screen
	{
		spri->start_line_img = 0; //we start from the beginning of the sprite since we will print it entirely
		spri->freq_pixel = (double)WALL_SIZE / (double)pix_spri2;
	}
	else	//sprite is taller than what we can print on screen. We will print only a portion of it
	{
		spri->start_line_img = (WALL_SIZE - (int)((double)WALL_SIZE *			//if no_limit == 400 and pix_spri == 200
					(double)pix_spri2 / (double)no_limit_pix_spri)) / 2;	//then we have to start at 25% of the sprite img
		spri->freq_pixel = (double)(WALL_SIZE - 2 * spri->start_line_img) / (double)pix_spri2;
	}
}

int		*sprite_addr(t_mlx *mlx, int type)
{
	int		*address;

	address = NULL;
	type == SP_GUARD ? address = mlx->addr.s_4 : 0;
	type == SP_TREE ? address = mlx->addr.s_5 : 0;
	type == SP_ARMOR ? address = mlx->addr.s_6 : 0;
	type == SP_HEALTH ? address = mlx->addr.s_7 : 0;
	type == SP_AMMO ? address = mlx->addr.s_8 : 0;
	type == SP_FLAG ? address = mlx->addr.s_9 : 0;
	return (address);
}

/*
** Set info *ptr on the correct sprite's informations and return int *ptr for
** addr.ptr of the correct sprite's address depending on type.
*/
int		*sprite_info_addr(t_mlx *mlx, int **info, int type)
{
	type == SP_GUARD ? *info = mlx->info.s_4 : 0;
	type == SP_TREE ? *info = mlx->info.s_5 : 0;
	type == SP_ARMOR ? *info = mlx->info.s_6 : 0;
	type == SP_HEALTH ? *info = mlx->info.s_7 : 0;
	type == SP_AMMO ? *info = mlx->info.s_8 : 0;
	type == SP_FLAG ? *info = mlx->info.s_9 : 0;
	return (sprite_addr(mlx, type));
}

/*
** Moving in sprite's address and returning the color of one pixel. We start
** from a certain row (depending where the ray touch the sprite), then we
** choose the line with start_line and freq_pixel.
*/
int		sprite_color(t_mlx *mlx, t_sprites *spri, int x, int type)
{
	int		row_img;
	int		*addr;
	int		*info;
	int		color;

	row_img = spri->row_percent * WALL_SIZE;
	x = (int)((double)x * spri->freq_pixel); //freq_pixel allows to repeat each pixel several time, depending on the distance
	addr = sprite_info_addr(mlx, &info, type); //info and addr.ptr are pointing to the correct sprite img
	if (x >= info[WIDTH])	//for avoiding segfault when round error with double
		x = info[WIDTH] - 1;
	if (type == SP_GUARD)
		color = addr[row_img + spri->guard.row_img + spri->guard.line_img * info[SIZE_LINE]
				+ spri->start_line_img * info[SIZE_LINE] + x * info[SIZE_LINE]];
	else
		color = addr[row_img + spri->start_line_img * info[SIZE_LINE] + x * info[SIZE_LINE]];
	return (color);
}

/*
** Sorts the tab of sprites based on each ray_len. Then for each sprite with a
** positive ray_len, calculates the height of the sprite in pixel and the
** frequency of pixel printing (depending on the distance to the sprite).
** Then fill the screen with sprite's pixels colors, and skip this step
** if it's the background color.
*/
void	draw_sprites(t_mlx *mlx, t_sprites **spri, int screen_row)
{
	int		i;
	int		x;
	int		nb_start_print;
	int		color;
	
	i = 0;
	sort_sprites_tab(spri); //sorting tab from the biggest ray_len to the smallest
	while (spri && spri[i] && spri[i]->ray_len >= 0.0)
	{
		spri[i]->nb_pix = height_object(mlx->cam, spri[i]->ray_len); //size of sprite in pixel
		sprite_resizing(mlx, spri[i], &(spri[i]->nb_pix)); //if nb_pix > reso y, now nb_pix = reso y
		nb_start_print = (int)((mlx->par->reso[1] - spri[i]->nb_pix) / 2.0); //starting from the top of projected sprite
		x = nb_start_print;
		while (x < nb_start_print + (int)(spri[i]->nb_pix))
		{
			color = sprite_color(mlx, spri[i], x - nb_start_print, spri[i]->type);
			if (color == spri[i]->inv_color) //skipping the printing if it's the background color
				x++;
			else
				mlx->addr.screen[screen_row + x++ * mlx->info.screen[SIZE_LINE]] = color;
		}
		i++;
	}
}
