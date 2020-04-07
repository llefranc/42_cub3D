/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:17:24 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/07 14:52:03 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CUBE3D_H
# define	CUBE3D_H

# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<math.h>
# include	<float.h>
# include	<time.h>
# include	<sys/time.h>

# include	"libftprintf.h"
# include	"mlx.h"
# include	"mlx_macro.h"
# include	"define.h"
# include	"structures.h"

/*
** ------ srcs_parsing -------
*/

int			error_msg(char *str, t_pars *par, char *line);
int			error_msg_map(char *str, t_pars *par, int *line);
int			check_arg(int ac, char **av);
void		free_split(char **split);
int			ft_strisdigit(char *str);
//check_arg.c

void		struct_init_par(t_pars *par);
void		struct_free(t_pars *par);
int			parsing(t_pars *par);
//parsing.c

int			key_type(char *line, t_pars *par);
void		key_check(t_pars *par);
//parsing_keys.c

int			parse_reso(t_pars *par, char *line);
int			parse_flo_rgb(t_pars *par, char *line);
int			parse_sky_rgb(t_pars *par, char *line);
int			parse_path(t_pars *par, char **path, char *line);
//parsing_elements.c

int			parse_map(t_pars *par, char *line);
int			map_check(t_pars *par);
//parsing_map.c

/*
** ----- srcs_raycasting -----
*/

double		positive_angle(double angle);
double		angle_tri_rect(double angle);
int			find_wall(t_rcast *cam, double angle, double x_len, double y_len);
double		ray_len(double xa, double ya, double xb, double yb);
double		height_object(t_rcast *cam, double ray_len);
double		nb_pixel_wall(t_mlx *mlx, t_rcast *cam, t_texture *textu, double angle);
//raycasting.c

double		x_ray_y1_value(t_rcast *cam, double angle);
double		x_ray_ya_value(double angle);
double		x_ray_x1_value(double angle, double y1);
double		x_ray_xa_value(double angle, double y1, double ya);
double		x_ray_len(t_mlx *mlx, t_rcast *cam, double angle, t_texture *textu);
//x_ray.c

double		y_ray_x1_value(t_rcast *cam, double angle);
double		y_ray_xa_value(double angle);
double		y_ray_y1_value(double angle, double x1);
double		y_ray_ya_value(double angle, double x1, double xa);
double		y_ray_len(t_mlx *mlx, t_rcast *cam, double angle, t_texture *textu);
//y_ray.c

void		reset_ray_len_sprites(t_sprites **spri);
void		calc_sprites_orientation(t_sprites **spri, double angle);
t_sprites	*sprites_ptr_x_ray(t_mlx *mlx, double angle, double x1, double y1);
t_sprites	*sprites_ptr_y_ray(t_mlx *mlx, double angle, double x1, double y1);
void		find_sprites(t_mlx *mlx, t_sprites *spri, double xd, double yd, double angle);
//sprites_raycast.c

int			floor_raycasting(t_mlx *mlx, double height, double rcast_angle);
int			draw_skybox(t_mlx *mlx, double height, double rcast_angle);
//floor_sky_raycast.c

/*
** ----- srcs_drawing -----
*/

void		destroy_all_images(t_mlx *mlx, t_img *img);
void		error_msg_destroy_img(const char *str, t_mlx *mlx);
void		struct_init_mlx(t_mlx *mlx);//, t_img *img, t_addr *addr, t_info *info);
//init_mlx_struct.c

void		free_sprite_struct(t_sprites **spri);
void		add_sprite_info(t_mlx *mlx, t_rcast *cam, int line, int row);
//init_sprite_struct.c

void		struct_init_camera(t_mlx *mlx, t_rcast *cam, t_pars *par);
//init_cam__struct.c

void		sort_sprites_tab(t_sprites **spri);
void		draw_sprites(t_mlx *mlx, t_sprites **spri, int screen_row);
//draw_sprites.c

void		draw_hud_and_gun_anims(t_mlx *mlx, t_pars *par, t_info *info);
//draw_hud.c

void		draw_colored_screen(t_mlx *mlx, int nb_pixel, int color);
void		player_is_dead(t_mlx *mlx);
void		draw_death_screen(t_mlx *mlx);
int			draw_level_menu(t_mlx *mlx);
//draw_level_menu.c

void		guards_animation(t_mlx *mlx, t_rcast *cam, t_sprites **spri);
//draw_ennemy.c

void		raycasting(t_mlx *mlx);
int			drawing(t_pars *par, int save);
//drawing.c

/*
** ----- srcs_event -----
*/

void		move_accords_framerate(t_mlx *mlx, double move);
void		rota_accords_framerate(t_mlx *mlx, double rota);
//movement.c

int			motion_notify(int x, int y, t_mlx *mlx);
int			key_press(int keycode, t_mlx *mlx);
int			key_release(int keycode, t_mlx *mlx);
int			destroy_notify(t_mlx *mlx);
int			no_event(t_mlx *mlx);
//events.c

void		open_door(t_mlx *mlx);
void		shoot_anim(t_mlx *mlx, t_rcast *cam);
//player_interactions.c

int			sprite_collision(t_mlx *mlx, t_rcast *cam, double xd, double yd);
//sprite_collision.c

int			x_ray_find_len_wall(t_mlx *mlx, double angle, double x_len, double y_len);
int			y_ray_find_len_wall(t_mlx *mlx, double angle, double x_len, double y_len);
double		x_ray_len_wall(t_mlx *mlx, t_rcast *cam, double angle);
double		y_ray_len_wall(t_mlx *mlx, t_rcast *cam, double angle);
void		check_guard_detect_player(t_mlx *mlx, t_rcast *cam, t_sprites *spri);
//detect_ennemy.c

void	save_image_as_bmp(t_mlx *mlx);
//save.c

#endif