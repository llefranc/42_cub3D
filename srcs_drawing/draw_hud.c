/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 16:41:11 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/25 17:17:44 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	draw_hud(t_mlx *mlx, t_pars *par, t_info *info)
{
	double	resize_w;	//to resize the width of the hud to fit the screen
	double	resize_h;
	double	row;
	double	line;
	
	resize_h = (par->reso[1] / (double)info->hud[HEIGHT]) * (1.0 / 6.0); //hud take 1/6 of screen's height
	resize_w = (par->reso[0] / (double)info->hud[WIDTH]); //take full screen's width
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < info->hud[HEIGHT])
	{
		row = 0.0;
		while ((int)(row / resize_w) < info->hud[WIDTH])
		{
			mlx->addr->screen[(int)row + (int)(mlx->par->reso[1] * (5.0 / 6.0)) * 	//we start at 5/6 of screen's height
					info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
					= mlx->addr->hud[(int)(row / resize_w) + (int)(line / resize_h)
					* info->hud[SIZE_LINE]];
			row += 1.0;
		}
		line += 1.0;
	}
}

void	draw_hud_anims(t_mlx *mlx, t_pars *par, t_info *info)
{
	draw_hud(mlx, par, info);
}
