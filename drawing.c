/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:07:23 by llefranc          #+#    #+#             */
/*   Updated: 2020/02/27 18:24:20 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

int		raycasting(t_pars *par)
{
	t_rcast cam;
	t_mlx mlx;

	struct_init_mlx(&mlx);
	struct_init_camera(par, &cam); //create a tab of **int for the map, from the prev map in **char
	cam.dist_screen = (par->reso[0] / 2.0) / tan((FOV / 2.0) * (TO_RAD)); //=277
	print_map(cam, 1);

	// cam.y -= 0.5;
	cam.x += 0.5;
	cam.angle = 0;
	printf("x = %f et y = %f, et angle = %f\n", cam.x, cam.y, cam.angle);
	printf("nb_rows = %d et nb_lines = %d\n", cam.nb_rows, cam.nb_lines);

	nb_pixel_wall(par, &cam, cam.angle);
	return (1);
}