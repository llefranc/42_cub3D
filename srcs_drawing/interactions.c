/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 14:52:42 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/25 16:15:49 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Using trigonometry to determinate new point's coordinates with a certain len.
*/
void	add_len_to_ray(t_mlx *mlx, t_point *square, double size_len)
{
	if (mlx->cam->angle >= 0.0 && mlx->cam->angle < 90.0)
	{
		square->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
	else if (mlx->cam->angle >= 90.0 && mlx->cam->angle < 180.0)
	{
		square->x += -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += -sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
	else if (mlx->cam->angle >= 180.0 && mlx->cam->angle < 270.0)
	{
		square->x += -cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
	else
	{
		square->x += cos(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
		square->y += sin(angle_tri_rect(mlx->cam->angle) * TO_RAD) * size_len;
	}
}

/*
** When a certain key is pressed, launch with a len of 1.0 in the direction of
** cam->angle and check every 0.1 unity if it encounters a door or a secret
** door. If it's the case, replace on the map the door value by 0.
*/
void	open_door(t_mlx *mlx)
{
	int		i;
	t_point	square;

	i = -1;
	square.x = mlx->cam->x; //we start from player position
	square.y = mlx->cam->y;
	while (++i < 10) //checking every 0.1 unity
	{
		add_len_to_ray(mlx, &square, 0.1);
		if (mlx->cam->map[(int)square.y][(int)square.x] == DOOR || //if door or secret door
				mlx->cam->map[(int)square.y][(int)square.x] == SECRETDOOR)
		{
			mlx->cam->map[(int)square.y][(int)square.x] = 0; //replace the value of the door' square
			return ;
		}
	}
}
