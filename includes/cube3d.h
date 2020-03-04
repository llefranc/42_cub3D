/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:17:24 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/04 12:22:35 by llefranc         ###   ########.fr       */
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

# include "libftprintf.h"
# include "mlx.h"
# include "mlx_macro.h"

//resolution values
#define RESO_MAX_X 2560
#define RESO_MIN_X 640 //PENSER A TCHECKER LE CAS DE LA RESO MIN
#define RESO_MAX_Y 1440
#define RESO_MIN_Y 480

//keys values
# define RESO 1
# define P_NORTH 2
# define P_SOUTH 3
# define P_EAST 4
# define P_WEST 5
# define P_SPRIT 6
# define FLO_RGB 7
# define SKY_RGB 8
# define MAP_LINE 9

//raycasting constants
# define WALL_SIZE 64	//height of wall
# define MOVE_SIZE 0.1
# define ROTA_SIZE 5.0
# define FOV 60			//field of view

//angle in degrees
# define V_EAST 0
# define V_NORTH 90
# define V_WEST 180
# define V_SOUTH 270

//usefull to convert degrees <=> radians
# define TO_DEG 180.0 / M_PI
# define TO_RAD M_PI / 180.0

//usefull for t_info structure, allow to move in the tab of 3 ints
// and selects the parameter expected
# define BITS_PER_PIX 0
# define SIZE_LINE 1
# define ENDIAN 2

//contains all the information from the config file
typedef struct	s_pars
{
	int			fd;			//for be allowed to closed flux when error occurs
	double		reso[2];	//reso x / reso y
	char		*path_no;	//path for finding north textures
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*path_sp;	//path for finding sprites
	int			flo_rgb;	//floor color contained in an int
	int			sky_rgb;	//sky color contained in a int
	char		**map;
}				t_pars;

typedef struct s_rcast
{
	double	angle;			//direction where player looks
	double	freq_ray;		//distance between to rays in degrees
	double	x;				//player position
	double	y;
	double	dist_screen;
	int		nb_rows;		//number of rows in the map, for avoiding segfault
	int		nb_lines;
	int		**map;
	t_pars	*par;			//allow to carry only t_rcast struct
}				t_rcast;

typedef struct s_img
{
	void	*screen;
}				t_img;

typedef struct s_addr
{
	int		*screen;
}				t_addr;

typedef struct s_info
{
	int		screen[3];
}				t_info;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	*img;
	t_addr	*addr;//implmentation endian ?
	t_info	*info;
	t_pars	*par;			//allow to carry only t_mlx struct
	t_rcast	*cam;
}				t_mlx;



void 	print_struct(t_pars *par); //a supprimer
void	print_map(t_rcast cam, int player); //a enlever
int		drawing(t_pars *par); //a modifier

/*
** ------ srcs_parsing -------
*/

//check_arg.c
int		error_msg(char *str, t_pars *par, char *line);
int		check_arg(int ac, char **av);
void	free_split(char **split);
int		ft_strisdigit(char *str);

//parsing.c
void	struct_init_par(t_pars *par);
void	struct_free(t_pars *par);
int		parsing(t_pars *par);

//parsing_keys.c
int		key_type(char *line, t_pars *par);
void	key_check(t_pars *par);

//parsing_elements.c
int		parse_reso(t_pars *par, char *line);
int		parse_flo_rgb(t_pars *par, char *line);
int		parse_sky_rgb(t_pars *par, char *line);
int		parse_path(t_pars *par, char **path, char *line);

//parsing_map.c
int		parse_map(t_pars *par, char *line);
int		map_check(t_pars *par);

/*
** ----- srcs_raycasting -----
*/

//raycasting.c
double	positive_angle(double angle);
double	angle_tri_rect(double angle);
int		find_wall(t_rcast *cam, double angle, double x_len, double y_len);
double	ray_len(t_rcast *cam, double x_len, double y_len);
int		nb_pixel_wall(t_rcast *cam, double angle);

//x_ray.c
double	x_ray_len(t_rcast *cam, double angle);

//y_ray.c
double	y_ray_len(t_rcast *cam, double angle);

/*
** ----- srcs_drawing -----
*/

void	struct_init_camera(t_pars *par, t_rcast *cam);
void	struct_init_mlx(t_mlx *mlx, t_img *img, t_addr *addr, t_info *info);

#endif