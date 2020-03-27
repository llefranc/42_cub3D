/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 16:41:11 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/27 11:19:07 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Draw the HUD on screen by respecting proportion with the screen and resizing
** the image.
*/
void	draw_hud(t_mlx *mlx, t_pars *par, t_info *info)
{
	double	resize_w;	//to resize the width of the hud to fit the screen
	double	resize_h;
	double	row;
	double	line;
	
	resize_h = (par->reso[1] / (double)info->hud[HEIGHT]) * (HUD_SIZE_H);
	resize_w = (par->reso[0] / (double)info->hud[WIDTH]); //take full screen's width
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < info->hud[HEIGHT])
	{
		row = 0.0;
		while ((int)(row / resize_w) < info->hud[WIDTH])
		{
			mlx->addr.screen[(int)row + (int)(mlx->par->reso[1] * (1.0 - HUD_SIZE_H)) * //we start at 5/6 of screen's height
					info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
					= mlx->addr.hud[(int)(row / resize_w) + (int)(line / resize_h)
					* info->hud[SIZE_LINE]];
			row += 1.0;
		}
		line += 1.0;
	}
}

int		lifebar_color(t_mlx *mlx, t_info *info, int row, int line)
{
	int		color;

	if (((double)row / (double)LIFE_PIX_W) < ((double)mlx->eve.life / (double)FULL_LIFE))
		color = mlx->addr.life[row + LIFE_RED_IMG_R + line * info->life[SIZE_LINE]
				+ LIFE_RED_IMG_L * info->life[SIZE_LINE]];
	else
		color = mlx->addr.life[row + LIFE_EMPTY_IMG_R + line * info->life[SIZE_LINE]
				+ LIFE_EMPTY_IMG_L * info->life[SIZE_LINE]];
	return (color);
}

void	draw_lifebar(t_mlx *mlx, t_pars *par, t_info *info)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;

	resize_h = (par->reso[1] / (double)LIFE_PIX_H) * (LIFE_SIZE_H);
	resize_w = (par->reso[0] / (double)LIFE_PIX_W) * (LIFE_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < LIFE_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < LIFE_PIX_W)
		{
			if (lifebar_color(mlx, info, (int)(row / resize_w), (int)(line / resize_h)) != INV_COLOR)
				mlx->addr.screen[(int)row + (int)((LIFE_SCREEN_R) * mlx->par->reso[0]) + (int)(mlx->par->reso[1]
						* LIFE_SCREEN_L) * info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
						= lifebar_color(mlx, info, (int)(row / resize_w), (int)(line / resize_h));
			row += 1.0;
		}
		line += 1.0;
	}
}

void	draw_hud_anims(t_mlx *mlx, t_pars *par, t_info *info)
{
	draw_hud(mlx, par, info);
	draw_lifebar(mlx, par, info);
}
