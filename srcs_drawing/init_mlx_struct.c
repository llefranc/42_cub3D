/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:23:29 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/06 11:48:08 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Destroy all images and windows previously loaded.
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
	img->life ? mlx_destroy_image(mlx->ptr, img->life) : 0;
	img->guns ? mlx_destroy_image(mlx->ptr, img->guns) : 0;
	img->num ? mlx_destroy_image(mlx->ptr, img->num) : 0;
	img->font ? mlx_destroy_image(mlx->ptr, img->font) : 0;
	img->screen ? mlx_destroy_image(mlx->ptr, img->screen) : 0;
	mlx->win ? mlx_destroy_window(mlx->ptr, mlx->win) : 0;
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
	destroy_all_images(mlx, &mlx->img);
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
	init_addr_info(&(addr->screen), mlx->img.screen, info->screen);
	init_addr_info(&(addr->t_no), mlx->img.t_no, info->t_no);
	init_addr_info(&(addr->t_so), mlx->img.t_so, info->t_so);
	init_addr_info(&(addr->t_ea), mlx->img.t_ea, info->t_ea);
	init_addr_info(&(addr->t_we), mlx->img.t_we, info->t_we);
	init_addr_info(&(addr->t_fl), mlx->img.t_fl, info->t_fl);
	init_addr_info(&(addr->t_sk), mlx->img.t_sk, info->t_sk);
	init_addr_info(&(addr->t_do), mlx->img.t_do, info->t_do);
	init_addr_info(&(addr->s_4), mlx->img.s_4, info->s_4);
	init_addr_info(&(addr->s_5), mlx->img.s_5, info->s_5);
	init_addr_info(&(addr->s_6), mlx->img.s_6, info->s_6);
	init_addr_info(&(addr->s_7), mlx->img.s_7, info->s_7);
	init_addr_info(&(addr->s_8), mlx->img.s_8, info->s_8);
	init_addr_info(&(addr->s_9), mlx->img.s_9, info->s_9);
	init_addr_info(&(addr->hud), mlx->img.hud, info->hud);
	init_addr_info(&(addr->life), mlx->img.life, info->life);
	init_addr_info(&(addr->guns), mlx->img.guns, info->guns);
	init_addr_info(&(addr->num), mlx->img.num, info->num);
	init_addr_info(&(addr->font), mlx->img.font, info->font);
}

/*
** Sets all img ptr to NULL to avoid error when one img failed to load and
** trying to destroying them in destroy_all_img func (if ptr == NULL, img
** load and no need to destroy it).
*/
void	struct_init_img_ptr_to_null(t_img *img)
{
	img->screen = NULL;
	img->t_no = NULL;
	img->t_so = NULL;
	img->t_ea = NULL;
	img->t_we = NULL;
	img->t_fl = NULL;
	img->t_sk = NULL;
	img->t_do = NULL;
	img->s_4 = NULL;
	img->s_5 = NULL;
	img->s_6 = NULL;
	img->s_7 = NULL;
	img->s_8 = NULL;
	img->s_9 = NULL;
	img->hud = NULL;
	img->life = NULL;
	img->guns = NULL;
	img->num = NULL;
	img->font = NULL;
}

/*
** Loads one specific sprite, using the path in argument.
*/
void	load_sprites(t_mlx *mlx, char *path, char *name, int num_sprite)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(path, name)))
		error_msg_destroy_img("Malloc failed\n", mlx);
	if (num_sprite == SP_GUARD && !(mlx->img.s_4 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.s_4[WIDTH]), &(mlx->info.s_4[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 5\n", mlx);
	if (num_sprite == SP_TREE && !(mlx->img.s_5 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.s_5[WIDTH]), &(mlx->info.s_5[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 5\n", mlx);
	else if (num_sprite == SP_ARMOR && !(mlx->img.s_6 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.s_6[WIDTH]), &(mlx->info.s_6[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 6\n", mlx);
	else if (num_sprite == SP_HEALTH && !(mlx->img.s_7 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.s_7[WIDTH]), &(mlx->info.s_7[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 7\n", mlx);
	else if (num_sprite == SP_AMMO && !(mlx->img.s_8 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.s_8[WIDTH]), &(mlx->info.s_8[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 8\n", mlx);
	else if (num_sprite == SP_FLAG && !(mlx->img.s_9 = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.s_9[WIDTH]), &(mlx->info.s_9[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading sprite number 9\n", mlx);
	else if (num_sprite == SP_HUD && !(mlx->img.hud = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.hud[WIDTH]), &(mlx->info.hud[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading HUD\n", mlx);
	else if (num_sprite == SP_LIFEBAR && !(mlx->img.life = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.life[WIDTH]), &(mlx->info.life[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading lifebar\n", mlx);
	else if (num_sprite == SP_GUNS && !(mlx->img.guns = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.guns[WIDTH]), &(mlx->info.guns[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading gun\n", mlx);
	else if (num_sprite == SP_NUMBERS && !(mlx->img.num = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.num[WIDTH]), &(mlx->info.num[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading numbers\n", mlx);
	else if (num_sprite == SP_FONT && !(mlx->img.font = mlx_xpm_file_to_image(mlx->ptr, tmp,
			&(mlx->info.font[WIDTH]), &(mlx->info.font[HEIGHT]))))
		error_msg_destroy_img("Sprites : error loading fonts\n", mlx);
	free(tmp);
}

/*
** Loading each images. 
*/
void	struct_init_img(t_mlx *mlx, t_info *info)
{
	struct_init_img_ptr_to_null(&mlx->img);
	mlx->img.screen = mlx_new_image(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1]);
	if (!(mlx->img.t_no = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_no, &(info->t_no[WIDTH]), &(info->t_no[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading north texture\n", mlx);
	if (!(mlx->img.t_so = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_so, &(info->t_so[WIDTH]), &(info->t_so[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading south texture\n", mlx);
	if (!(mlx->img.t_ea = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_ea, &(info->t_ea[WIDTH]), &(info->t_ea[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading east texture\n", mlx);
	if (!(mlx->img.t_we = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_we, &(info->t_we[WIDTH]), &(info->t_we[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading west texture\n", mlx);
	if (!(mlx->img.t_fl = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_b_fl, &(info->t_fl[WIDTH]), &(info->t_fl[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading floor texture\n", mlx);
	if (!(mlx->img.t_sk = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_b_sk, &(info->t_sk[WIDTH]), &(info->t_sk[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading sky texture\n", mlx);
	if (!(mlx->img.t_do = mlx_xpm_file_to_image(mlx->ptr, mlx->par->path_b_do, &(info->t_do[WIDTH]), &(info->t_do[HEIGHT]))))
		error_msg_destroy_img("Textures : error loading door texture\n", mlx);
	load_sprites(mlx, mlx->par->path_sp, "num_4/guard.xpm", SP_GUARD);
	load_sprites(mlx, mlx->par->path_sp, "num_5/tree.xpm", SP_TREE);
	load_sprites(mlx, mlx->par->path_sp, "num_6/armor.xpm", SP_ARMOR);
	load_sprites(mlx, mlx->par->path_sp, "num_7/health.xpm", SP_HEALTH);
	load_sprites(mlx, mlx->par->path_sp, "num_8/spears.xpm", SP_AMMO);
	load_sprites(mlx, mlx->par->path_sp, "num_9/flag.xpm", SP_FLAG);
	load_sprites(mlx, mlx->par->path_sp, "hud.xpm", SP_HUD);
	load_sprites(mlx, mlx->par->path_sp, "lifebar.xpm", SP_LIFEBAR);
	load_sprites(mlx, mlx->par->path_sp, "guns.xpm", SP_GUNS);
	load_sprites(mlx, mlx->par->path_sp, "numbers.xpm", SP_NUMBERS);
	load_sprites(mlx, mlx->par->path_sp, "font.xpm", SP_FONT);
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
	eve->ammo = AMMO_START;
	eve->player_is_shooting = 0;
	eve->gun_shot = 0;
	eve->lifebar = FULL_LIFE;
	eve->level = 0;
	eve->nb_life = 0; //will be initiated after player choose level, in function draw_level_menu
}

/*
** Init a mlx struct. Create a mlx->ptr with mlx_init() and a new window for
** mlx->win. Loads the differents images on mlx.img, and filled the addresses
** and informations of those images in respectively mlx.addr and mlx.info.
*/
void	struct_init_mlx(t_mlx *mlx)//, t_img *img, t_addr *addr, t_info *info)
{
	mlx->start_move.tv_sec = 0.0; //booleans for movement and rotation
	mlx->start_rota.tv_sec = 0.0;
	mlx->spri = NULL;
	mlx->ptr = mlx_init();
	mlx->win = mlx_new_window(mlx->ptr, (int)mlx->par->reso[0], (int)mlx->par->reso[1], "cub3d");
	struct_init_paths(mlx, mlx->par);
	struct_init_img(mlx, &mlx->info);
	struct_init_addr_info(mlx, &mlx->addr, &mlx->info);
	struct_init_events_bool(&mlx->eve);
}
