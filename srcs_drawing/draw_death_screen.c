/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_death_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/01 17:26:29 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/01 19:51:29 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Return pixel's color of one letter.
*/
int		font_color(t_mlx *mlx, int row, int line, int c)
{
	int		color;
	int		row_start;
	int		line_start;
	
	c -= 'A';
	row_start = c % 8 * FONT_PIX_W;
	line_start = c / 8 * FONT_PIX_H;
	color = mlx->addr.font[row + line * mlx->info.font[SIZE_LINE] + row_start
			+ line_start * mlx->info.font[SIZE_LINE]];
	return (color);
}

/*
** Resizes and draws a letter at a certain position indiacted by row_screen.
*/
void	draw_letter(t_mlx *mlx, t_info *info, double row_screen, char c)
{
	double	resize_w;
	double	resize_h;
	double	row;
	double	line;
	
	resize_h = (mlx->par->reso[1] / (double)FONT_PIX_H) * (FONT_SIZE_H); //resizing letter
	resize_w = (mlx->par->reso[0] / (double)FONT_PIX_W) * (FONT_SIZE_W);
	line = 0.0;
	row = 0.0;
	while ((int)(line / resize_h) < FONT_PIX_H)
	{
		row = 0.0;
		while ((int)(row / resize_w) < FONT_PIX_W)
		{
			if (font_color(mlx, (int)(row / resize_w), (int)(line / resize_h), (int)c) != INV_COLOR) //if not background color
			//printing letter at correct position on screen
				mlx->addr.screen[(int)row + (int)(row_screen * mlx->par->reso[0]) 
						+ (int)(mlx->par->reso[1] * FONT_SCREEN_L) * info->screen[SIZE_LINE] +
						(int)line * info->screen[SIZE_LINE]]
						= font_color(mlx, (int)(row / resize_w), (int)(line / resize_h), (int)c);
			row += 1.0;
		}
		line += 1.0;
	}

}

/*
** Draws on sreen "gameover".
*/
void	draw_gameover_message(t_mlx *mlx)
{
	int		i;

	i = 0;
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'G');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'A');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'M');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'E');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'O');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'V');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'E');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'R');
}

/*
** Draws on sreen "you are dead".
*/
void	draw_you_are_dead_message(t_mlx *mlx)
{
	int		i;

	i = -2; //we have to print two more letters than with gameover
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'Y');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'O');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'U');
	i++; //space
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'A');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'R');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'E');
	i++;
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'D');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'E');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'A');
	draw_letter(mlx, &mlx->info, FONT_SCREEN_R + FONT_SIZE_W * i++, 'D');
}

/*
** Draws a colored screen and a message when the player dies.
*/
void	draw_colored_screen(t_mlx *mlx, int nb_pixel, int color)
{
	int		i;

	i = 0;
	if (nb_pixel <= 0)
		return ;
	while (i < (int)mlx->par->reso[1] * mlx->info.screen[SIZE_LINE])
	{
		mlx->addr.screen[i] = color;
		i += nb_pixel;	//if nb_pixel == 1, screen is fill
	}					//if nb_pixel = 5, every 5 pixels will be colored
	mlx->eve.nb_life > 1 ? draw_you_are_dead_message(mlx) : 0;
	mlx->eve.nb_life == 1 ? draw_gameover_message(mlx) : 0;
}

/*
** Draws progressively a death screen and a message when the player dies. If he
** still has lives, he will respawn from the start position with full health
** and less one life.
*/
void	draw_death_screen(t_mlx *mlx)
{
	int				i;
	struct timeval	end;
	double			time; //in ms

	i = 0;
	gettimeofday(&end, NULL);
	time = (double)(end.tv_usec - mlx->eve.time_player_death.tv_usec)
			/ 1000000.0 + (double)(end.tv_sec - mlx->eve.time_player_death.tv_sec);
	if (time < 0.01)	//to actualize lifebar when death player occurs
		draw_hud_and_gun_anims(mlx, mlx->par, &mlx->info);
	if (mlx->eve.nb_life > 1 && time < 3.0) //colored screen will appear slowly during 2 sec and last 1 sec
		draw_colored_screen(mlx, (int)((2.0 - time) * 10.0), 0x0); //red transition screen between respawn
	else if (mlx->eve.nb_life > 1) //if the player respawns
	{
		mlx->eve.nb_life--;
		mlx->eve.lifebar = FULL_LIFE;
		mlx->cam->x = mlx->eve.start_pos_x; //starting from start position previously saved
		mlx->cam->y = mlx->eve.start_pos_y;
		mlx->cam->angle = mlx->eve.start_angle;
	}
	else
		draw_colored_screen(mlx, (int)((2.0 - time) * 10.0), 0x0); //gameover, esc for quit
}