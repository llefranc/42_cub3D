/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:23:29 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/23 11:34:00 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Destroy all images previously loaded.
*/
void	destroy_all_images(t_mlx *mlx, t_img *img)
{
	img->t_no ? mlx_destroy_image(mlx->ptr, img->t_no) : 0;
	img->t_so ? mlx_destroy_image(mlx->ptr, img->t_so) : 0;
	img->t_ea ? mlx_destroy_image(mlx->ptr, img->t_ea) : 0;
	img->t_we ? mlx_destroy_image(mlx->ptr, img->t_we) : 0;
	img->t_fl ? mlx_destroy_image(mlx->ptr, img->t_fl) : 0;
	img->t_sk ? mlx_destroy_image(mlx->ptr, img->t_sk) : 0;
	img->s_2 ? mlx_destroy_image(mlx->ptr, img->s_2) : 0;
	img->screen ? mlx_destroy_image(mlx->ptr, img->screen) : 0;
}

/*
** Free properly parsing and sprites structs, then destroy all images
** previously loaded, print an error message and exit.
*/
void	error_msg_destroy_img(const char *str, t_mlx *mlx)
{
	ft_printf("Error\n%s", str);
	if (mlx->par)
		struct_free(mlx->par); //also close file descriptor
	if (mlx->spri)
		free_sprite_struct(mlx->spri);
	destroy_all_images(mlx, mlx->img);
	exit(EXIT_FAILURE);
}

/*
** Getting addresses and informations of each images loaded.
*/
void	struct_init_addr_info(t_mlx *mlx, t_addr *addr, t_info *info)
{
	addr->screen = (int *)mlx_get_data_addr(mlx->img->screen, &(info->screen[BITS_PER_PIX]), 
			&(info->screen[SIZE_LINE]), &(info->screen[ENDIAN]));
	info->screen[SIZE_LINE] /= (info->screen[BITS_PER_PIX] / 8); //to fill the colors with 1 int value and not 3 bytes RGB
	addr->t_no = (int *)mlx_get_data_addr(mlx->img->t_no, &(info->t_no[BITS_PER_PIX]), 
			&(info->t_no[SIZE_LINE]), &(info->t_no[ENDIAN]));
	info->t_no[SIZE_LINE] /= (info->t_no[BITS_PER_PIX] / 8);
	addr->t_so = (int *)mlx_get_data_addr(mlx->img->t_so, &(info->t_so[BITS_PER_PIX]), 
			&(info->t_so[SIZE_LINE]), &(info->t_so[ENDIAN]));
	info->t_so[SIZE_LINE] /= (info->t_so[BITS_PER_PIX] / 8);
	addr->t_ea = (int *)mlx_get_data_addr(mlx->img->t_ea, &(info->t_ea[BITS_PER_PIX]), 
			&(info->t_ea[SIZE_LINE]), &(info->t_ea[ENDIAN]));
	info->t_ea[SIZE_LINE] /= (info->t_ea[BITS_PER_PIX] / 8);
	addr->t_we = (int *)mlx_get_data_addr(mlx->img->t_we, &(info->t_we[BITS_PER_PIX]), 
			&(info->t_we[SIZE_LINE]), &(info->t_we[ENDIAN]));
	info->t_we[SIZE_LINE] /= (info->t_we[BITS_PER_PIX] / 8);
	addr->t_fl = (int *)mlx_get_data_addr(mlx->img->t_fl, &(info->t_fl[BITS_PER_PIX]), 
			&(info->t_fl[SIZE_LINE]), &(info->t_fl[ENDIAN]));
	info->t_fl[SIZE_LINE] /= (info->t_fl[BITS_PER_PIX] / 8);
	addr->t_sk = (int *)mlx_get_data_addr(mlx->img->t_sk, &(info->t_sk[BITS_PER_PIX]), 
			&(info->t_sk[SIZE_LINE]), &(info->t_sk[ENDIAN]));
	info->t_sk[SIZE_LINE] /= (info->t_sk[BITS_PER_PIX] / 8);
	addr->s_2 = (int *)mlx_get_data_addr(mlx->img->s_2, &(info->s_2[BITS_PER_PIX]), 
			&(info->s_2[SIZE_LINE]), &(info->s_2[ENDIAN]));
	info->s_2[SIZE_LINE] /= (info->s_2[BITS_PER_PIX] / 8);

}

/*
** Loads one specific sprite, using the path in argument.
*/
void	load_sprites(t_mlx *mlx, char *path, char *name, int num_sprite)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(path, name)))
		error_msg_destroy_img("Malloc failed\n", mlx);
	if (num_sprite == 2)
		if (!(mlx->img->s_2 = mlx_xpm_file_to_image(mlx->ptr, tmp, 
				&(mlx->info->s_2[WIDTH]), &(mlx->info->s_2[HEIGHT]))))
			error_msg_destroy_img("Textures : error loading sprite number 2\n", mlx);
	free(tmp);
}

/*
** Loading each images. 
*/
void	struct_init_img(t_mlx *mlx, t_info *info)
{
	mlx->img->screen = mlx_new_image(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1]);
	if (!(mlx->img->t_no = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_no, &(info->t_no[WIDTH]), &(info->t_no[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading north texture\n", mlx);
	if (!(mlx->img->t_so = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_so, &(info->t_so[WIDTH]), &(info->t_so[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading south texture\n", mlx);
	if (!(mlx->img->t_ea = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_ea, &(info->t_ea[WIDTH]), &(info->t_ea[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading east texture\n", mlx);
	if (!(mlx->img->t_we = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_we, &(info->t_we[WIDTH]), &(info->t_we[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading west texture\n", mlx);
	if (!(mlx->img->t_fl = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_b_fl, &(info->t_fl[WIDTH]), &(info->t_fl[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading floor texture\n", mlx);
	if (!(mlx->img->t_sk = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_b_sk, &(info->t_sk[WIDTH]), &(info->t_sk[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading sky texture\n", mlx);
	load_sprites(mlx, mlx->par->path_sp, "num_2/tree.xpm", 2);
}

/*
** Join the path of one file and his filename, and then free the path.
*/
void	join_path_filename(t_mlx *mlx, char **path, char *name)
{
	char	*tmp;

	tmp = *path;
	if (!(*path = ft_strjoin(*path, name)))
		error_msg_destroy_img("Malloc failed\n", mlx);
	free(tmp);
}

/*
** Add the filename to the path for each textures / sprites.
*/
void	struct_init_paths(t_mlx *mlx, t_pars *par)
{
	join_path_filename(mlx, &(par->path_no), "t_north.xpm");
	join_path_filename(mlx, &(par->path_so), "t_south.xpm");
	join_path_filename(mlx, &(par->path_ea), "t_east.xpm");
	join_path_filename(mlx, &(par->path_we), "t_west.xpm");
	join_path_filename(mlx, &(par->path_b_fl), "t_floor.xpm");
	join_path_filename(mlx, &(par->path_b_sk), "t_skybox.xpm");
}

/*
** Init a mlx struct. Create a mlx->ptr with mlx_init() and a new window for
** mlx->win, links addr, img, info structures to mlx. Loads the differents
** images on mlx->img, and filled the addresses and informations of those
** images in respectively mlx->addr and mlx->info.
*/
void	struct_init_mlx(t_mlx *mlx, t_img *img, t_addr *addr, t_info *info)
{
	mlx->start_move = 0; //booleans for movement and rotation
	mlx->start_rota = 0;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1], "cub3d");
	mlx->img = img;
	mlx->addr = addr;
	mlx->info = info;
	struct_init_paths(mlx, mlx->par);
	struct_init_img(mlx, info);
	struct_init_addr_info(mlx, addr, info);
	mlx->spri = NULL;
}
