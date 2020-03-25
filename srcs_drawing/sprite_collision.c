/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 10:45:30 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/24 13:35:12 by lucaslefran      ###   ########.fr       */
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

/*
** Determinate if player movement (j vector) is not crossing sprite's plan
** (i vector). Add 0.7 to the len of j vector so the player can't get to close
** to the sprites. If the player is passing through sprite's plan, the function
** return 1. Otherwise return 0.
*/
int		find_inter_rays(t_mlx *mlx, t_sprites *spri, double xc, double yc)
{
	t_point d;
	t_point vec_i;		//represent AB segment
	t_point vec_j;		//represent CD segment
	double	k;			//len of AB line when it's crossing CD, should be < 1.0 if it occurs on segment AB
	double	m;			//len of CD line when it's crossing AB, same
	double	seg_len;	//ratio to add 0.7 len to CD vector, so player is not to close from sprite

	d.x = mlx->cam->x;
	d.y = mlx->cam->y;
	vec_j.x = d.x - xc;	//coordinates of j vector (temporary calcul)
	vec_j.y = d.y - yc;
	seg_len = ray_len(d.x, d.y, xc, yc);
	seg_len = 0.7 / seg_len;
	d.x += vec_j.x * seg_len; //new d point coordinates, we add 0.7 len to CD segment
	d.y += vec_j.y * seg_len; //in order to not be to close to sprites
	vec_i.x = spri->b_sized.x - spri->a_sized.x;	//coordinates of i vector
	vec_i.y = spri->b_sized.y - spri->a_sized.y;
	vec_j.x = d.x - xc;					//coordinates of j vector with new d point (len of j extended by 0.7)
	vec_j.y = d.y - yc;
	m = -(-vec_i.x * spri->a_sized.y + vec_i.x * yc + vec_i.y * spri->a_sized.x - vec_i.y * xc) 
			/ (vec_i.x * vec_j.y - vec_i.y * vec_j.x);
	k = -(spri->a_sized.x * vec_j.y - xc * vec_j.y - vec_j.x * spri->a_sized.y + vec_j.x * yc)
			/ (vec_i.x * vec_j.y - vec_i.y * vec_j.x);
	if (m > 0.0 && m < 1.0 && k > 0.0 && k < 1.0) //segment AB and CD are crossing each other
		return (1); //so no deplacement because movement is passing through sprite
	return (0);
}

/*
** Checking if when player movement is not encountering a sprite. If the player
** is passing through a sprite, return 1. Otherwise return 0.
*/
int			sprite_collision(t_mlx *mlx, t_rcast *cam, double xc, double yc)
{
	t_sprites	*square1;
	t_sprites	*square2;

	square1 = sprite_ptr(mlx, (int)cam->x, (int)cam->y);
	if ((int)cam->x == (int)xc && (int)cam->y == yc) //movement only inside one square
		square2 = NULL;
	else			//if the movement is to one square to another one
		square2 = sprite_ptr(mlx, (int)xc, (int)yc);
	if (square1 && find_inter_rays(mlx, square1, xc, yc)) //on square 1, player is passing through a sprite
		return (1);
	if (square2 && find_inter_rays(mlx, square2, xc, yc)) //on square 2, player is passing through a sprite
		return (1);
	return (0);
}
