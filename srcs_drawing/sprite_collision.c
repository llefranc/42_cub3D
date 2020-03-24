/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 10:45:30 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/24 11:46:38 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Return a t_sprite *ptr if there if the square (x, y) is a sprite. Otherwise
** return NULL.
*/
t_sprites	*sprite_ptr(t_mlx *mlx, int x, int y)
{
	int			i;

	i = 0;
	while (mlx->spri && mlx->spri[i] && (mlx->spri[i]->y != y || mlx->spri[i]->x != x))
		i++;
	if (!mlx->spri)	//in case of no sprites in the map
		return (NULL);
	return (mlx->spri[i]);
}

int		find_inter_rays(t_mlx *mlx, t_sprites *spri, double xd, double yd)
{
	t_point c;
	t_point vec_i;	//represent AB segment
	t_point vec_j;	//represent CD segment
	double	k;		//len of AB line when it's crossing CD, should be < 1.0 if it occurs on segment AB
	double	m;		//len of CD line when it's crossing AB, same

	c.x = mlx->cam->x;
	c.y = mlx->cam->y;
	vec_i.x = spri->b_sized.x - spri->a_sized.x;	//coordinates of i vector
	vec_i.y = spri->b_sized.y - spri->a_sized.y;
	vec_j.x = xd - c.x;					//coordinates of j vector
	vec_j.y = yd - c.y;
	m = -(-vec_i.x * spri->a_sized.y + vec_i.x * c.y + vec_i.y * spri->a_sized.x - vec_i.y * c.x) 
			/ (vec_i.x * vec_j.y - vec_i.y * vec_j.x);
	k = -(spri->a_sized.x * vec_j.y - c.x * vec_j.y - vec_j.x * spri->a_sized.y + vec_j.x * c.y)
			/ (vec_i.x * vec_j.y - vec_i.y * vec_j.x);
	if (m > 0.0 && m < 1.0 && k > 0.0 && k < 1.0) //segment AB and CD are crossing each other
		return (1); //so no deplacement because movement is passing through sprite
	return (0);
}

int			sprite_collision(t_mlx *mlx, t_rcast *cam, double xd, double yd)
{
	t_sprites	*square1;
	t_sprites	*square2;
		
	square1 = sprite_ptr(mlx, (int)cam->x, (int)cam->y);
	if ((int)cam->x == (int)xd && (int)cam->y == yd) //movement only inside one square
		square2 = NULL;
	else			//if the movement is to one square to another one
		square2 = sprite_ptr(mlx, (int)xd, (int)yd);
	if (square1 && find_inter_rays(mlx, square1, xd, yd)) //on square 1, player is passing through a sprite
		return (1);
	if (square2 && find_inter_rays(mlx, square2, xd, yd)) //on square 2, player is passing through a sprite
		return (1);
	return (0);
}
