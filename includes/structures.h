/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:37:29 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/08 12:33:59 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		STRUCTURES_H
# define	STRUCTURES_H

# include	"cube3d.h"

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

typedef struct		s_guard
{
	int				status;			//if the guard is seeing the player (0 if not, 1 if starting seeing, 2 when fighting)
	int				row_img;
	int				line_img;
	int				shooting;
	struct timeval	time_detect;
	struct timeval	time_death;
}					t_guard;

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
	double			x;					//sprite's coordinates (peut etre les passer en double pour les gardes ?)
	double			y;
	double			ray_len;			//len of the ray when it meets the sprite
	double			nb_pix;				//number of pixels print on screen for the sprite
	int				start_line_img;		//first line of the image that we will print (for resizing)
	double			freq_pixel;			//nb of time one pixel should be print (for resizing)
	double			row_percent;		//portion of the sprite image touched by the ray
	t_point			a;					//segment AB is the plan of the sprite, always facing and perpendicular
	t_point			b;					//to the angle of the camere
	t_point			a_sized;			//segment AB_sized is the same than AB, except is also including sprite' size
	t_point			b_sized;			//when printing on screen (if tree has a width of 32 pix, AB_sized is half of AB)
	t_guard			guard;
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
	int				ammo;				//number of ammo
	int				player_is_shooting;	//boolean to indicate if shooting key is pressed or not	
	int				gun_shot;			//boolean to start shooting anim
	struct timeval	gun_time_start;		//time when player press key for shoot
	int				lifebar;			//lifebar (from 0 to 100)
	int				level;
	int				nb_life;
	double			start_pos_x;		//player's informations to restart from beginning
	double			start_pos_y;		//position if he dies
	double			start_angle;
	struct timeval	time_player_death;
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
	void			*life;
	void			*guns;
	void			*num;
	void			*font;
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
	int				*life;
	int				*guns;
	int				*num;
	int				*font;
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
	int				life[5];
	int				guns[5];
	int				num[5];
	int				font[5];
}					t_info;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	struct timeval	start_move;			//for actualizing player's movements and rotation according to time
	struct timeval	start_rota;			//and avoid framerate drops
	t_img			img;				//allow to carry only t_mlx struct
	t_addr			addr;
	t_info			info;
	t_pars			*par;
	t_rcast			*cam;
	t_event			eve;
	t_texture		*textu;
	t_sprites		**spri;
}					t_mlx;

#endif