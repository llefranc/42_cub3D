/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:17:24 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/18 16:07:41 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "libftprintf.h"
# include "mlx.h"

# define BUFF_GNL 1024

#define RESO_MAX_X 1920
#define RESO_MIN_X 640
#define RESO_MAX_Y 1080
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

typedef struct	s_cube
{
	int			fd;
	int			reso[2];
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*path_sp;
	int			flo_rgb[3];
	int			sky_rgb[3];
	char		**map;
}				t_cube;

void print_struct(t_cube *par); //a supprimer
/*
** ----- srcs_parsing -----
*/

//get_next_line.c
int		get_next_line(int fd, char **line); //penser a changer peut etre le get next line

//check_arg.c
int		error_msg(char *str, t_cube *par, char *line);
int		check_arg(int ac, char **av);
void	free_split(char **split);
int		ft_strisdigit(char *str);

//parsing.c
void	struct_init(t_cube *par);
void	struct_free(t_cube *par);
int		parsing(t_cube *par);

//parsing_keys.c
int		key_type(char *line, t_cube *par);
void	key_check(t_cube *par);

//parsing_elements.c
int		parse_reso(t_cube *par, char *line);
int		parse_flo_rgb(t_cube *par, char *line);
int		parse_sky_rgb(t_cube *par, char *line);
int		parse_path(t_cube *par, char **path, char *line);

//parsing_map.c
int		parse_map(t_cube *par, char *line);
int		map_check(t_cube *par);

#endif