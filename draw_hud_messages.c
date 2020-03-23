/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 11:55:31 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/23 12:23:05 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

// void	mouse_message(t_mlx *mlx, t_pars *par)
// {
// 	static clock_t	start;
// 	clock_t			end;

// 	if (mlx->cam->mouse_msg == 1)
// 	{
// 		start = clock();
// 		mlx->cam->mouse_msg = 2;
// 	}
// 	end = clock();
// 	if ((end - start) / CLOCKS_PER_SEC < 1.0)
// 	{
// 		mlx->cam->mouse_bool ? mlx_string_put(mlx->ptr, mlx->win, par->reso[0] / 2.0, //CREER ICI NOTRE PROPRE FONCTION
// 				par->reso[1] * 0.75, 0, "Mouse activated") : 0;							//POUR PRINT DES MESSAGES SOUS FORME DE SPRITE
// 		!mlx->cam->mouse_bool ? mlx_string_put(mlx->ptr, mlx->win, par->reso[0] / 2.0,
// 				par->reso[1] * 0.75, 0, "Mouse desactivated") : 0;
// 	}
// 	else
// 		mlx->cam->mouse_msg = 0;
// }

// void	draw_hud_messages(t_mlx *mlx, t_pars *par)
// {
// 	mlx->cam->mouse_msg ? mouse_message(mlx, par) : 0;
// }
