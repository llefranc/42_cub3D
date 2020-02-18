/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:02:13 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/19 00:24:46 by lucaslefran      ###   ########.fr       */
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
	t_image *square = (t_image *)param;
	// printf("%d\n", keycode);
	//w = 13, a = 0, s = 1, d = 2
	if (keycode == 13)
		(square->y) -=  4;
	else if (keycode == 1)
		(square->y) += 4;
	else if (keycode == 0)
		(square->x) -= 4;
	else if (keycode == 2)
		(square->x) += 4;
	int y = 0;
	mlx_clear_window(square->mlx_ptr, square->win_ptr);
	mlx_put_image_to_window(square->mlx_ptr, square->win_ptr, square->img_ptr2, 10, 10);
	while (y <= 480)
		mlx_pixel_put(square->mlx_ptr, square->win_ptr, 200, y++, square->color);
	mlx_string_put(square->mlx_ptr, square->win_ptr, 300, 300, square->color, "salut codebrai");
	mlx_put_image_to_window(square->mlx_ptr, square->win_ptr, square->img_ptr, square->x, square->y);
	return (1);
}

void	fill_image_with_color(char *img_addr, int size_line, int max_ligne)
{
	int i;
	int j;

	i = 0;
	while (max_ligne-- > 0)
	{
		j = 0;
		while (j < size_line)
		{
			*(((int *)img_addr) + i) = int_color(0, 255, 0); 
			i += 1;
			j += 4;
		}
	}
}

int main(void)
{
	void *mlx_ptr = NULL;
	void *win_ptr;
	void *img_ptr;
	void *florian;
	int orange;
	t_image square;

	if (!(mlx_ptr = mlx_init()))
		printf("error mlx_init\n");
	if (!(win_ptr = mlx_new_window(mlx_ptr, 640, 480, "corentin le pd")))
		printf("error create new window\n");
	orange = int_color(255, 165, 0);
	square.mlx_ptr = mlx_ptr;
	square.win_ptr = win_ptr;
	square.color = orange;
	square.x = 10;
	square.y = 10;
	mlx_do_key_autorepeaton(mlx_ptr); //marche pas
	mlx_string_put(mlx_ptr, win_ptr, 300, 300, orange, "salut codebrai");
	int y = 0;
	while (y <= 480)
		mlx_pixel_put(mlx_ptr, win_ptr, 200, y++, orange);
	img_ptr = mlx_new_image(mlx_ptr, 243, 241);
	square.img_ptr = img_ptr;
	int nb1;
	int nb2;
	int nb3;
	char *img_addr;
	img_addr =  mlx_get_data_addr(img_ptr, &nb1, &nb2, &nb3);
	printf("int = %d et unsigned int = %u\n", orange, mlx_get_color_value(mlx_ptr, orange));
	fill_image_with_color(img_addr, nb2, 241);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 10, 10);
	square.img_ptr2 = img_ptr;
	int width = 200;
	int height = 200;
	if (!(square.img_ptr = mlx_xpm_file_to_image(mlx_ptr, "florian.xpm", &width, &height)))
		printf("erreur chargement image\n");
	printf("widht = %d et heighjt = %d\n", width, height);
	mlx_put_image_to_window(mlx_ptr, win_ptr, square.img_ptr, 300, 10);
	square.x = 300;
	mlx_key_hook(win_ptr, &key_hook, (void *)&square);
	mlx_loop(mlx_ptr);
	return (0);
}