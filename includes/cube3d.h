/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:17:24 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/25 16:49:57 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <float.h>
# include <time.h>
# include <sys/time.h>

# include "libftprintf.h"
# include "mlx.h"
# include "mlx_macro.h"

//resolution values
# define RESO_MAX_X		2560
# define RESO_MAX_Y		1440

//keys values
# define RESO			1
# define P_NORTH		2
# define P_SOUTH		3
# define P_EAST			4
# define P_WEST			5
# define P_SPRIT		6
# define P_B_FLOOR		7
# define P_B_SKY		8
# define P_B_DOOR		9
# define FLO_RGB		10
# define SKY_RGB		11
# define MAP_LINE		12

//values for N/W/E/S - 48 (ASCII values)
# define NORTH			30
# define SOUTH			35
# define EAST			21
# define WEST			39

//raycasting constants
# define WALL_SIZE		64			//height of wall
# define MOVE_SIZE		0.065
# define TIME_MOVE		0.015
# define ROTA_SIZE		2.5
# define M_ROTA_SIZE	0.75
# define FOV			50			//field of view

//angle in degrees
# define V_EAST			0
# define V_NORTH		90
# define V_WEST			180
# define V_SOUTH		270

//usefull to convert degrees <=> radians
# define TO_DEG			180.0 / M_PI
# define TO_RAD			M_PI / 180.0

//usefull for t_info structure, allow to move in the tab of 3 ints
//and selects the parameter expected
# define BITS_PER_PIX	0
# define SIZE_LINE		1
# define ENDIAN			2
# define WIDTH			3
# define HEIGHT			4

//types of doors
# define DOOR			2
# define SECRETDOOR		3


//types of sprite
# define SP_TREE		4
# define SP_ARMOR		5
# define SP_HEALTH		6
# define SP_LAMP		7
# define SP_SPEARS		8
# define SP_FLAG		9
# define SP_HUD			10
# define SP_LIFEBAR		11
# define SP_GUNS		12

//width (in pixel) of sprites on screen for sprite collision
# define TREE_SIZE		20
# define ARMOR_SIZE		30
# define HEALTH_SIZE	40
# define LAMP_SIZE		0
# define SPEARS_SIZE	50
# define FLAG_SIZE		16

//contains all the information from the config file
typedef struct		s_pars
{
	int				fd;					//for be allowed to closed flux when error occurs
	double			reso[2];			//reso x / reso y
	char			*path_no;			//path for finding north textures
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	char			*path_sp;			//path for finding sprites
	char			*path_b_fl;			//path for bonus floor texture 
	char			*path_b_sk;			//path for bonus sky texture 
	char			*path_b_do;			//path for bonus door
	char			*path_b_sd;			//path for bonus secret door
	int				flo_rgb;			//floor color contained in an int
	int				sky_rgb;			//sky color contained in a int
	int				**map;
}					t_pars;

//allows to print the textures for walls
typedef struct		s_texture
{
	double			x_xa;				//save coordinates of the wall hitted by x_ray
	double			x_ya;
	double			y_xa;				//same but for y_ray
	double			y_ya;
	double			angle_raycast;		//for determinate side_wall
	int				side_wall;			//NORTH, SOUTH... for printing different textures on walls
	int				doors_x;			//if x_ray touch a door / secret door
	int				doors_y;
	int				no_limit_pix_wall;	//can be larger then reso y >> if the texture is taller than the reso
	int				start_line_img;		//when huge texture, for starting to print from a certain height
	double			freq_pixel;			//for printing several times or not some pixels (allow to resize texture)
	int				row_img;			//row of the texture that we have to print on the wall
}					t_texture;

//represent the coordinates of one point
typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

//allows to print sprites
typedef struct		s_sprites
{
	int				type;				//value of the sprite on the map (2, 3, 4..)
	int				size;				//width (in pixel) of sprite on screen
	int				*addr_img;			//memory adress of the sprite image
	int				inv_color;			//color that we're not printing for the sprite's background
	int				x;					//sprite's coordinates
	int				y;
	double			ray_len;			//len of the ray when it meets the sprite
	double			nb_pix;				//number of pixels print on screen for the sprite
	int				start_line_img;		//first line of the image that we will print (for resizing)
	double			freq_pixel;			//nb of time one pixel should be print (for resizing)
	double			row_percent;		//portion of the sprite image touched by the ray
	t_point			a;					//segment AB is the plan of the sprite, always facing and perpendicular
	t_point			b;					//to the angle of the camere
	t_point			a_sized;			//segment AB_sized is the same than AB, except is also including sprite' size
	t_point			b_sized;			//when printing on screen (if tree has a width of 32 pix, AB_sized is half of AB)
}					t_sprites;

//handle raycasting + player's movements events
typedef struct		s_rcast
{
	double			angle;				//direction where player looks
	double			freq_ray;			//distance between to rays in degrees
	double			x;					//player position
	double			y;
	double			dist_screen;
	int				*nb_rows;			//number of rows in the map for each line, for avoiding segfault
	int				nb_lines;
	int				m_up;				//booleans for movement (be able to press multiple keys)
	int				m_down;
	int				m_left;
	int				m_right;
	int				r_left;				//booleans for rotation with keyboard
	int				r_right;
	double			rm_left;			//value of rotation with mouse
	double			rm_right;
	int				mouse_bool;			//for rotation with mouse
	int				mouse_x;
	int				**map;
	t_pars			*par;				//allow to carry only t_rcast struct
}					t_rcast;

//handle events and interactions with player
typedef struct		s_event
{
	int				print_texture;		//boolean to print or not floor and sky textures
}					t_event;

//t_* == textures || s_* == sprites
typedef struct		s_img
{
	void			*screen;
	void			*t_no;				//north
	void			*t_so;
	void			*t_ea;
	void			*t_we;
	void			*t_fl;				//floor
	void			*t_sk;				//sky (skybox)
	void			*t_do;				//door
	void			*s_4;				//sprite number 4
	void			*s_5;
	void			*s_6;
	void			*s_7;
	void			*s_8;
	void			*s_9;
	void			*hud;
}					t_img;

typedef struct		s_addr
{
	int				*screen;
	int				*t_no;
	int				*t_so;
	int				*t_ea;
	int				*t_we;
	int				*t_fl;
	int				*t_sk;
	int				*t_do;
	int				*s_4;
	int				*s_5;
	int				*s_6;
	int				*s_7;
	int				*s_8;
	int				*s_9;
	int				*hud;
}					t_addr;

typedef struct		s_info
{
	int				screen[5];			//[0] = BITS_PER_PIX
	int				t_no[5];			//[1] = SIZE_LINE
	int				t_so[5];			//[2] = ENDIAN
	int				t_ea[5];			//[3] = WIDTH (only for xpm images)
	int				t_we[5];			//[4] = HEIGHT (only for xpm images)
	int				t_fl[5];
	int				t_sk[5];
	int				t_do[5];
	int				s_4[5];
	int				s_5[5];
	int				s_6[5];
	int				s_7[5];
	int				s_8[5];
	int				s_9[5];
	int				hud[5];
}					t_info;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	struct timeval	start_move;			//for actualizing player's movements and rotation according to time
	struct timeval	start_rota;			//and avoid framerate drops
	t_img			*img;				//allow to carry only t_mlx struct
	t_addr			*addr;//implmentation endian ?
	t_info			*info;
	t_pars			*par;
	t_rcast			*cam;
	t_event			*eve;
	t_texture		*textu;
	t_sprites		**spri;
}					t_mlx;


void	 	print_struct(t_pars *par); //a supprimer
void		print_map(int **map); //a enlever
int			drawing(t_pars *par); //a modifier
void		raycasting(t_mlx *mlx);

/*
** ------ srcs_parsing -------
*/

//check_arg.c
int			error_msg(char *str, t_pars *par, char *line);
int			error_msg_map(char *str, t_pars *par, int *line);
int			check_arg(int ac, char **av);
void		free_split(char **split);
int			ft_strisdigit(char *str);

//parsing.c
void		struct_init_par(t_pars *par);
void		struct_free(t_pars *par);
int			parsing(t_pars *par);

//parsing_keys.c
int			key_type(char *line, t_pars *par);
void		key_check(t_pars *par);

//parsing_elements.c
int			parse_reso(t_pars *par, char *line);
int			parse_flo_rgb(t_pars *par, char *line);
int			parse_sky_rgb(t_pars *par, char *line);
int			parse_path(t_pars *par, char **path, char *line);

//parsing_map.c
int			parse_map(t_pars *par, char *line);
int			map_check(t_pars *par);

/*
** ----- srcs_raycasting -----
*/

//raycasting.c
double		positive_angle(double angle);
double		angle_tri_rect(double angle);
int			find_wall(t_rcast *cam, double angle, double x_len, double y_len);
double		ray_len(double xa, double ya, double xb, double yb);
double		height_object(t_rcast *cam, double ray_len);
double		nb_pixel_wall(t_mlx *mlx, t_rcast *cam, t_texture *textu, double angle);

//x_ray.c
double		x_ray_len(t_mlx *mlx, t_rcast *cam, double angle, t_texture *textu);

//y_ray.c
double		y_ray_len(t_mlx *mlx, t_rcast *cam, double angle, t_texture *textu);

//sprites_raycast.c
void		reset_ray_len_sprites(t_sprites **spri);
void		calc_sprites_orientation(t_sprites **spri, double angle);
t_sprites	*sprites_ptr_x_ray(t_mlx *mlx, double angle, double x1, double y1);
t_sprites	*sprites_ptr_y_ray(t_mlx *mlx, double angle, double x1, double y1);
void		find_sprites(t_mlx *mlx, t_sprites *spri, double xd, double yd, double angle);

//floor_sky_raycast.c
int			floor_raycasting(t_mlx *mlx, double height, double rcast_angle);
int			draw_skybox(t_mlx *mlx, double height, double rcast_angle);

/*
** ----- srcs_drawing -----
*/

//init_mlx_struct.c
void		destroy_all_images(t_mlx *mlx, t_img *img);
void		error_msg_destroy_img(const char *str, t_mlx *mlx);
void		struct_init_mlx(t_mlx *mlx, t_img *img, t_addr *addr, t_info *info);

//init_sprite_struct.c
void		free_sprite_struct(t_sprites **spri);
void	add_sprite_info(t_mlx *mlx, t_rcast *cam, int line, int row);

//init_cam__struct.c
void		struct_init_camera(t_mlx *mlx, t_rcast *cam, t_pars *par);

//movement.c
void		move_accords_framerate(t_mlx *mlx, double move);
void		rota_accords_framerate(t_mlx *mlx, double rota);

//events.c
int			motion_notify(int x, int y, t_mlx *mlx);
int			key_press(int keycode, t_mlx *mlx);
int			key_release(int keycode, t_mlx *mlx);
int			destroy_notify(t_mlx *mlx);
int			no_event(t_mlx *mlx);

//interactions.c
void		open_door(t_mlx *mlx);

//draw_sprites.c
void		draw_sprites(t_mlx *mlx, t_sprites **spri, int screen_row);


//sprite_collision.c
int			sprite_collision(t_mlx *mlx, t_rcast *cam, double xd, double yd);

//draw_hud_messages.c A ENLEVER ?????
void		draw_hud_messages(t_mlx *mlx, t_pars *par);
//draw_hud_anims.c
void		draw_hud_anims(t_mlx *mlx, t_pars *par, t_info *info);


#endif