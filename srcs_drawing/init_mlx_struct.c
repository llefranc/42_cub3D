/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:23:29 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/25 16:50:41 by lucaslefran      ###   ########.fr       */
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
	img->t_do ? mlx_destroy_image(mlx->ptr, img->t_do) : 0;
	img->s_4 ? mlx_destroy_image(mlx->ptr, img->s_4) : 0;
	img->s_5 ? mlx_destroy_image(mlx->ptr, img->s_5) : 0;
	img->s_6 ? mlx_destroy_image(mlx->ptr, img->s_6) : 0;
	img->s_7 ? mlx_destroy_image(mlx->ptr, img->s_7) : 0;
	img->s_8 ? mlx_destroy_image(mlx->ptr, img->s_8) : 0;
	img->s_9 ? mlx_destroy_image(mlx->ptr, img->s_9) : 0;
	img->hud ? mlx_destroy_image(mlx->ptr, img->hud) : 0;
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

void	init_addr_info(int **addr, void *img, int info[5])
{
	*addr = (int *)mlx_get_data_addr(img, &(info[BITS_PER_PIX]), 
			&(info[SIZE_LINE]), &(info[ENDIAN]));
	info[SIZE_LINE] /= (info[BITS_PER_PIX] / 8); //to fill the colors with 1 int value and not 3 bytes RGB
}

/*
** Getting addresses and informations of each images loaded.
*/
void	struct_init_addr_info(t_mlx *mlx, t_addr *addr, t_info *info)
{
	init_addr_info(&(addr->screen), mlx->img->screen, info->screen);
	init_addr_info(&(addr->t_no), mlx->img->t_no, info->t_no);
	init_addr_info(&(addr->t_so), mlx->img->t_so, info->t_so);
	init_addr_info(&(addr->t_ea), mlx->img->t_ea, info->t_ea);
	init_addr_info(&(addr->t_we), mlx->img->t_we, info->t_we);
	init_addr_info(&(addr->t_fl), mlx->img->t_fl, info->t_fl);
	init_addr_info(&(addr->t_sk), mlx->img->t_sk, info->t_sk);
	init_addr_info(&(addr->t_do), mlx->img->t_do, info->t_do);
	init_addr_info(&(addr->s_4), mlx->img->s_4, info->s_4);
	init_addr_info(&(addr->s_5), mlx->img->s_5, info->s_5);
	init_addr_info(&(addr->s_6), mlx->img->s_6, info->s_6);
	init_addr_info(&(addr->s_7), mlx->img->s_7, info->s_7);
	init_addr_info(&(addr->s_8), mlx->img->s_8, info->s_8);
	init_addr_info(&(addr->s_9), mlx->img->s_9, info->s_9);
	init_addr_info(&(addr->hud), mlx->img->hud, info->hud);
}

/*
** Loads one specific sprite, using the path in argument.
*/
void	load_sprites(t_mlx *mlx, char *path, char *name, int num_sprite)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(path, name)))
		error_msg_destroy_img("Malloc failed\n", mlx);
	if (num_sprite == SP_TREE && !(mlx->img->s_4 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info->s_4[WIDTH]), &(mlx->info->s_4[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 4\n", mlx);
	else if (num_sprite == SP_ARMOR && !(mlx->img->s_5 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info->s_5[WIDTH]), &(mlx->info->s_5[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 5\n", mlx);
	else if (num_sprite == SP_HEALTH && !(mlx->img->s_6 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info->s_6[WIDTH]), &(mlx->info->s_6[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 6\n", mlx);
	else if (num_sprite == SP_LAMP && !(mlx->img->s_7 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info->s_7[WIDTH]), &(mlx->info->s_7[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 7\n", mlx);
	else if (num_sprite == SP_SPEARS && !(mlx->img->s_8 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info->s_8[WIDTH]), &(mlx->info->s_8[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 8\n", mlx);
	else if (num_sprite == SP_FLAG && !(mlx->img->s_9 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info->s_9[WIDTH]), &(mlx->info->s_9[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 9\n", mlx);
	else if (num_sprite == SP_HUD && !(mlx->img->hud = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info->hud[WIDTH]), &(mlx->info->hud[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading HUD\n", mlx);
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
	if (!(mlx->img->t_do = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_b_do, &(info->t_do[WIDTH]), &(info->t_do[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading door texture\n", mlx);
	load_sprites(mlx, mlx->par->path_sp, "num_4/tree.xpm", SP_TREE);
	load_sprites(mlx, mlx->par->path_sp, "num_5/armor.xpm", SP_ARMOR);
	load_sprites(mlx, mlx->par->path_sp, "num_6/health.xpm", SP_HEALTH);
	load_sprites(mlx, mlx->par->path_sp, "num_7/lamp.xpm", SP_LAMP);
	load_sprites(mlx, mlx->par->path_sp, "num_8/spears.xpm", SP_SPEARS);
	load_sprites(mlx, mlx->par->path_sp, "num_9/flag.xpm", SP_FLAG);
	load_sprites(mlx, mlx->par->path_sp, "hud.xpm", SP_HUD);
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
	join_path_filename(mlx, &(par->path_no), "north.xpm");
	join_path_filename(mlx, &(par->path_so), "south.xpm");
	join_path_filename(mlx, &(par->path_ea), "east.xpm");
	join_path_filename(mlx, &(par->path_we), "west.xpm");
	join_path_filename(mlx, &(par->path_b_fl), "floor.xpm");
	join_path_filename(mlx, &(par->path_b_sk), "skybox.xpm");
	join_path_filename(mlx, &(par->path_b_do), "door.xpm");
}

/*
** initiates all booleans values.
*/
void	struct_init_events_bool(t_event *eve)
{
	eve->print_texture = 1;
}

/*
** Init a mlx struct. Create a mlx->ptr with mlx_init() and a new window for
** mlx->win, links addr, img, info structures to mlx. Loads the differents
** images on mlx->img, and filled the addresses and informations of those
** images in respectively mlx->addr and mlx->info.
*/
void	struct_init_mlx(t_mlx *mlx, t_img *img, t_addr *addr, t_info *info)
{
	mlx->start_move.tv_sec = 0.0; //booleans for movement and rotation
	mlx->start_rota.tv_sec = 0.0;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1], "cub3d");
	mlx->img = img;
	mlx->addr = addr;
	mlx->info = info;
	struct_init_paths(mlx, mlx->par);
	struct_init_img(mlx, info);
	struct_init_addr_info(mlx, addr, info);
	struct_init_events_bool(mlx->eve);
	mlx->spri = NULL;
}
