/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:02:13 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/18 20:41:37 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"
#include "test.h"

//prend un couple rgb ety renvoie l'int correspondant
int		int_color(unsigned char red, unsigned char green, unsigned char blue)
{
	int color;

	*((char *)&color) = blue; 
	*((char *)&color + 1) = green; 
	*((char *)&color + 2) = red; 
	return (color);
}

int   key_hook(int keycode, void *param)
{
	printf("%d\n", keycode);

	return (1);
}

int   key_hook2(int keycode, void *param)
{
	printf("salut %d\n", keycode);

	return (1);
}

int main(void)
{
	void *mlx_ptr = NULL;
	void *win_ptr;
	int orange;

	if (!(mlx_ptr = mlx_init()))
		printf("error mlx_init\n");
	if (!(win_ptr = mlx_new_window(mlx_ptr, 640, 480, "corentin le pd")))
		printf("error create new window\n");
	orange = int_color(255, 165, 0);
	mlx_string_put(mlx_ptr, win_ptr, 300, 300, orange, "salut codebrai");
	int y = 0;
	while (y <= 480)
		mlx_pixel_put(mlx_ptr, win_ptr, 200, y++, orange);
	mlx_key_hook(win_ptr, &key_hook2, NULL);
	mlx_key_hook(win_ptr, &key_hook, NULL);
	mlx_loop(mlx_ptr);
	return (0);
}