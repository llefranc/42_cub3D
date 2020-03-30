/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ennemy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/29 13:49:39 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/30 10:25:20 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Return value of the angle made by a ray (between the player and the guard)
** in a trigonometric environnement (360 degrees).
*/
double	find_angle(t_rcast *cam, t_sprites *guard)
{
	double	x_len;
	double	y_len;
	double	angle;

	x_len = fabs(guard->x - cam->x); //evolving in rectangle triange
	y_len = fabs(guard->y - cam->y);
	angle = atan(y_len / x_len) * TO_DEG;
	// printf("angle = %f, x = %f, y = %f\n", angle, x_len, y_len);
	if (guard->x < cam->x && guard->y < cam->y)	//translating angle from a rectangle triangle (90 degrees)
		angle = 180.0 - angle;					//into trigonometry environnement (360 degrees)
	else if (guard->x < cam->x && guard->y >= cam->y)
		angle = 180.0 + angle;
	else if (guard->x >= cam->x && guard->y < cam->y)
		angle = 360.0 - angle;
	return (angle);
}

void	check_guard_detect_player(t_mlx *mlx, t_rcast *cam, t_sprites *guard)
{
	double	angle;

	(void)mlx;
	angle = find_angle(cam, guard);
}

void	guards_seeing_player(t_mlx *mlx, t_rcast *cam, t_sprites **spri)
{
	int		i;

	i = -1;
	while (spri[++i])
		if (spri[i]->type == SP_GUARD)
			check_guard_detect_player(mlx, cam, spri[i]);
}
