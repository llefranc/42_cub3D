/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 15:04:29 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/31 15:05:17 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Allow to print one guard sprite by indicating the position of this one in an
** image containing all the guard sprites.
*/
void	initialize_guard_sprite(t_sprites *spri, int line, int row)
{
	spri->guard.line_img = line;
	spri->guard.row_img = row;
}

/*
** 
*/
void	guard_anim_alive(t_event *player, t_sprites *spri)
{
	double			time;		//in ms
	int				time_tmp;	//using an int (ms * 100), in order to be able to use modulo
	struct timeval	end;		//and choose more easily the timers for animations

	if (spri->guard.status >= DYING)
		return ;
	gettimeofday(&end, NULL);
	time = 0.0;
	spri->guard.status == DETECTING_PLAYER ? time = (double)(end.tv_usec - spri->guard.time_detect.tv_usec)
			/ 1000000.0 + (double)(end.tv_sec - spri->guard.time_detect.tv_sec) : 0;
	time_tmp = (int)(time * 100.0);
	if (!spri->guard.status || time_tmp < 50)	//basic guard sprite
		initialize_guard_sprite(spri, G_BASIC_L, G_BASIC_R);
	else if (time_tmp < 100)						//guard in alert, just detected the player
		initialize_guard_sprite(spri, G_DETECT_L, G_DETECT_R);
	else if (time_tmp % 180 < 165)					//guard aiming at the player, shoot every 1,40 sec
	{
		spri->guard.shooting = 0;
		initialize_guard_sprite(spri, G_SHOOT_L, G_SHOOT1_R);
	}
	else											//guard shoot (anim last 0.15 sec)
	{
		!spri->guard.shooting ? player->lifebar -= 10 : 0;	//if first time we're entering in shooting anim
		player->lifebar < 0 ? player->lifebar = 0 : 0;
		spri->guard.shooting = 1;	//for removing player's life only once per shooting anim
		initialize_guard_sprite(spri, G_SHOOT_L, G_SHOOT2_R);
	}
}

void	guard_anim_dead(t_sprites *spri)
{
	double			time;		//in ms
	struct timeval	end;

	gettimeofday(&end, NULL);
	time = 0.0;
	if (spri->guard.status == DEAD)
	{
		initialize_guard_sprite(spri, G_DEAD_L, G_DEAD5_R);
		return ;
	}
	time = (double)(end.tv_usec - spri->guard.time_death.tv_usec)
			/ 1000000.0 + (double)(end.tv_sec - spri->guard.time_death.tv_sec);
	if (time < 0.1)
		initialize_guard_sprite(spri, G_DEAD_L, G_DEAD1_R);
	else if (time < 0.2)
		initialize_guard_sprite(spri, G_DEAD_L, G_DEAD2_R);
	else if (time < 0.3)
		initialize_guard_sprite(spri, G_DEAD_L, G_DEAD3_R);
	else if (time < 0.4)
		initialize_guard_sprite(spri, G_DEAD_L, G_DEAD4_R);
	else
		spri->guard.status = DEAD;
}

void	guards_seeing_player(t_mlx *mlx, t_rcast *cam, t_sprites **spri) //rename cette fonction
{
	int		i;

	i = -1;
	while (spri[++i])
	{
		if (spri[i]->type == SP_GUARD)
			check_guard_detect_player(mlx, cam, spri[i]);
	}
	i = -1;
	while (spri[++i])
	{
		if (spri[i]->type == SP_GUARD && spri[i]->guard.status <= DETECTING_PLAYER)
			guard_anim_alive(&mlx->eve, spri[i]);
		if (spri[i]->type == SP_GUARD && spri[i]->guard.status >= DYING)
			guard_anim_dead(spri[i]);
	}
}
