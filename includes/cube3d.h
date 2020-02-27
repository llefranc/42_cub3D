/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:17:24 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/27 18:11:13 by llefranc         ###   ########.fr       */
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
# define WALL_SIZE 64 //height of wall
# define SIZE_MOVE 0.01
# define FOV 60 //field of view

//angle in degrees
# define V_EAST 0
# define V_NORTH 90
# define V_WEST 180
# define V_SOUTH 270

//usefull to convert degrees <=> radians
# define TO_DEG 180 / M_PI
# define TO_RAD M_PI / 180

typedef struct	s_pars
{
	int			fd;
	double		reso[2];
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*path_sp;
	int			flo_rgb;//transformer en int dans le parsing
	int			sky_rgb;//transformer en int dans le parsing
	char		**map;
}				t_pars; //changer en t_pars

typedef struct s_rcast
{
	int		**map;
	double	angle;
	double	dist_screen;
	double	x;
	double	y;
	int		nb_rows;
	int		nb_lines;
	t_pars	*par;
}				t_rcast;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*img_screen;
	int		*img_addr;//implmentation endian ?
	int		size_line;
	int		endian; //rajouter l'inmplemntation endian
}				t_mlx;

void 	print_struct(t_pars *par); //a supprimer
void	print_map(t_rcast cam, int player); //a enlever
int		raycasting(t_pars *par); //a modifier

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
double	angle_tri_rect(double angle);
int		find_wall(t_rcast *cam, double angle, double x_len, double y_len);
double	ray_len(t_rcast *cam, double x_len, double y_len);
int		nb_pixel_wall(t_pars *par, t_rcast *cam, double angle);

//x_ray.c
double	x_ray_len(t_rcast *cam, double angle);

//y_ray.c
double	y_ray_len(t_rcast *cam, double angle);

/*
** ----- srcs_drawing -----
*/

int		**struct_init_camera(t_pars *par, t_rcast *cam);
void	struct_init_mlx(t_mlx *mlx);


#endif