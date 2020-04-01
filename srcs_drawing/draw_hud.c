/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 16:41:11 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/01 16:29:17 by lucaslefran      ###   ########.fr       */
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

/*
** Return pixel's color of the red lifebar or grey lifebar depending on
** player's life.
*/
int		lifebar_color(t_mlx *mlx, t_info *info, int row, int line)
{
	int		color;

	if (((double)row / (double)LIFE_PIX_W) < ((double)mlx->eve.lifebar / (double)FULL_LIFE)) //red lifebar
		color = mlx->addr.life[row + LIFE_RED_IMG_R + line * info->life[SIZE_LINE]
				+ LIFE_RED_IMG_L * info->life[SIZE_LINE]];	//starting at correct position in sprite img
	else
		color = mlx->addr.life[row + LIFE_EMPTY_IMG_R + line * info->life[SIZE_LINE]
				+ LIFE_EMPTY_IMG_L * info->life[SIZE_LINE]];
	return (color);
}

/*
** Draw the lifebar on screen by respecting proportion with the screen and
** resizing the image.
*/
void	draw_lifebar(t_mlx *mlx, t_pars *par, t_info *info)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;

	resize_h = (par->reso[1] / (double)LIFE_PIX_H) * (LIFE_SIZE_H); //resizing lifebar
	resize_w = (par->reso[0] / (double)LIFE_PIX_W) * (LIFE_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < LIFE_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < LIFE_PIX_W)
		{
			if (lifebar_color(mlx, info, (int)(row / resize_w), (int)(line / resize_h)) != INV_COLOR) //if not background color
				//printing lifebar at correct position on screen
				mlx->addr.screen[(int)row + (int)((LIFE_SCREEN_R) * mlx->par->reso[0]) + (int)(mlx->par->reso[1]
						* LIFE_SCREEN_L) * info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
						= lifebar_color(mlx, info, (int)(row / resize_w), (int)(line / resize_h));
			row += 1.0;
		}
		line += 1.0;
	}
}

/*
** Return pixel's color of one of the five sprites of shooting animation.
*/
int		gun_color(t_mlx *mlx, int num_sprite, int row, int line)
{
	int		color;
	
	color = mlx->addr.guns[row + GUNS_IMG_R * num_sprite + line * mlx->info.guns[SIZE_LINE]
			+ GUNS_IMG_L * mlx->info.guns[SIZE_LINE]];	//starting at correct position in sprite img
	return (color);
}

/*
** Draw gun's animations by respecting proportion with the screen and
** resizing the image.
*/
void	draw_gun(t_mlx *mlx, t_pars *par, t_info *info, int num_sprite)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;

	resize_h = (par->reso[1] / (double)GUNS_PIX_H) * (GUNS_SIZE_H); //resizing gun
	resize_w = (par->reso[0] / (double)GUNS_PIX_W) * (GUNS_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < GUNS_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < GUNS_PIX_W)
		{
			if (gun_color(mlx, num_sprite, (int)(row / resize_w), (int)(line / resize_h)) != INV_COLOR) //if not background color
			//printing gun at correct position on screen
				mlx->addr.screen[(int)row + (int)((GUNS_SCREEN_R) * mlx->par->reso[0]) + (int)(mlx->par->reso[1]
						* GUNS_SCREEN_L) * info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
						= gun_color(mlx, num_sprite, (int)(row / resize_w), (int)(line / resize_h));
			row += 1.0;
		}
		line += 1.0;
	}
}

/*
** Return pixel's color of of one of the ten numbers, all in the same image.
** Multiplicates num variable with the width of one number in pixel (+1 because
** they're seprarayed by a white line) to find the right number.
*/
int		number_color(t_mlx *mlx, int num, int row, int line)
{
	int		color;
	
	color = mlx->addr.num[row + NUMBER_IMG_R + num * (NUMBER_PIX_W + 1) 	//starting at correct position in sprite img
			+ line * mlx->info.num[SIZE_LINE] + NUMBER_IMG_L * mlx->info.num[SIZE_LINE]];
	return (color);
}

/*
** Draw a number on screen at a certain position indicated by row_screen. No
** need to line_screen because all hud numbers are on the same line. The int
** num indicates which number need to be draw.
*/
void	draw_number(t_mlx *mlx, t_info *info, int num, double row_screen)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;

	resize_h = (mlx->par->reso[1] / (double)NUMBER_PIX_H) * (NUMBER_SIZE_H); //resizing number
	resize_w = (mlx->par->reso[0] / (double)NUMBER_PIX_W) * (NUMBER_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < NUMBER_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < NUMBER_PIX_W)
		{
			if (number_color(mlx, num, (int)(row / resize_w), (int)(line / resize_h)) != INV_COLOR) //if not background color
			//printing number at correct position on screen
				mlx->addr.screen[(int)row + (int)((row_screen) * mlx->par->reso[0]) + (int)(mlx->par->reso[1]
						* NUMBER_SCREEN_L) * info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
						= number_color(mlx, num, (int)(row / resize_w), (int)(line / resize_h));
			row += 1.0;
		}
		line += 1.0;
	}
}

/*
** Draws life percent, ammos and level number.
*/
void	draw_all_hud_numbers(t_mlx *mlx, t_info *info)
{
	if (mlx->eve.lifebar == 100) //need to draw 3 numbers
	{
		draw_number(mlx, info, 1, N_LIFE1_SCREEN_R);
		draw_number(mlx, info, 0, N_LIFE2_SCREEN_R);
	}
	else
		mlx->eve.lifebar / 10 > 0  ? draw_number(mlx, info, mlx->eve.lifebar / 10, N_LIFE2_SCREEN_R) : 0;
	draw_number(mlx, info, mlx->eve.lifebar % 10, N_LIFE3_SCREEN_R); //last number of lifebar will be always draw
	mlx->eve.ammo >= 10 ? draw_number(mlx, info, mlx->eve.ammo / 10, N_AMMO1_SCREEN_R) : 0;
	draw_number(mlx, info, mlx->eve.ammo % 10, N_AMMO2_SCREEN_R); //last number of ammo will be always draw
	draw_number(mlx, info, mlx->eve.level, N_LEVEL_SCREEN_R);
}

/*
** Return pixel's color of one heart.
*/
int		heart_color(t_mlx *mlx, int row, int line)
{
	int		color;
	
	color = mlx->addr.life[row + HEART_IMG_R + line * mlx->info.life[SIZE_LINE]
			+ HEART_IMG_L * mlx->info.life[SIZE_LINE]]; //starting at correct position in sprite img
	return (color);
}

/*
** Resizes and draws a heart at a certain position indiacted by row_screen.
*/
void	draw_one_heart(t_mlx *mlx, t_pars *par, t_info *info, double row_screen)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;
	
	resize_h = (par->reso[1] / (double)HEART_PIX_H) * (HEART_SIZE_H); //resizing heart
	resize_w = (par->reso[0] / (double)HEART_PIX_W) * (HEART_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < HEART_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < HEART_PIX_W)
		{
			if (heart_color(mlx, (int)(row / resize_w), (int)(line / resize_h)) != INV_COLOR) //if not background color
			//printing heart at correct position on screen
				mlx->addr.screen[(int)row + (int)((row_screen) * mlx->par->reso[0]) + (int)(mlx->par->reso[1]
						* HEART_SCREEN_L) * info->screen[SIZE_LINE] + (int)line * info->screen[SIZE_LINE]]
						= heart_color(mlx, (int)(row / resize_w), (int)(line / resize_h));
			row += 1.0;
		}
		line += 1.0;
	}
}

/*
** Draws 1, 2 or 3 hearts on HUD depending on player's lifes.
*/
void	draw_lives(t_mlx *mlx, t_pars *par, t_info *info)
{
	mlx->eve.nb_life == 3 ? draw_one_heart(mlx, par, info, HEART1_SCREEN_R) : 0;
	mlx->eve.nb_life >= 2 ? draw_one_heart(mlx, par, info, HEART2_SCREEN_R) : 0;
	draw_one_heart(mlx, par, info, HEART3_SCREEN_R);
}

/*
** Draws HUD, lifebar and gun on screen. Uses a timer for shooting animation,
** in order to know which sprite of the animation should be print on screen.
** Refresh animation every 15 ms.
*/
void	draw_hud_anims(t_mlx *mlx, t_pars *par, t_info *info)
{
	int						num_sprite_gun;
	double					time;
	static struct timeval	end;

	num_sprite_gun = 0; //basic gun sprite, when no anim
	gettimeofday(&end, NULL);
	if (mlx->eve.gun_shot) //if player pressed shooting key
	{
		time = (double)(end.tv_usec - mlx->eve.gun_time_start.tv_usec) / 1000000.0 +
        (double)(end.tv_sec - mlx->eve.gun_time_start.tv_sec);
		num_sprite_gun = 1 + (int)(time * 15.0); //printing different sprites depending on time spent since key pressed
		num_sprite_gun >= 5 ? mlx->eve.gun_shot = 0 : 0; //5 gun's sprites (from 0 to 4). At 5, the animation is ended
		num_sprite_gun >= 5 ? num_sprite_gun = 4 : 0;
	}
	draw_gun(mlx, par, info, num_sprite_gun);
	draw_hud(mlx, par, info);
	draw_lifebar(mlx, par, info);
	draw_lives(mlx, par, info);
	draw_all_hud_numbers(mlx, info);
}
