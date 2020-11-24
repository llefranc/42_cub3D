# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 18:41:15 by llefranc          #+#    #+#              #
#    Updated: 2020/11/24 17:29:36 by lucaslefran      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
FRAMEWORKS	=	-framework OpenGL -framework AppKit

SRCS_PA		=	main.c check_map.c init_and_errors.c parsing_elements.c \
				parsing_keys.c parsing_map.c parsing.c
SRCS_RA		=	floor_sky_raycast.c raycasting.c sprites_raycast.c x_ray.c y_ray.c
SRCS_EV		=	detect_ennemy.c events.c movement.c player_interactions.c \
				save.c sprite_collision.c
SRCS_DR		=	draw_death_screen.c draw_ennemy.c draw_hud.c draw_level_menu.c \
				draw_sprites.c drawing.c init_cam_struct.c init_mlx_struct.c \
				init_sprite_struct.c

LIB			=	libftprintf.a libmlx.a

OBJS_PA		=	$(SRCS_PA:.c=.o)
OBJS_RA		=	$(SRCS_RA:.c=.o)
OBJS_EV		=	$(SRCS_EV:.c=.o)
OBJS_DR		=	$(SRCS_DR:.c=.o)

PATH_LIB	=	lib/
PATH_DR		=	srcs_drawing/
PATH_EV		=	srcs_events/
PATH_PA		=	srcs_parsing/
PATH_RA		=	srcs_raycasting/

all		: 	$(NAME)

bonus	:	$(NAME)

$(NAME)	:	$(addprefix $(PATH_DR), $(OBJS_DR)) $(addprefix $(PATH_EV), $(OBJS_EV)) \
			$(addprefix $(PATH_PA), $(OBJS_PA)) $(addprefix $(PATH_RA), $(OBJS_RA))
			$(CC) -o $(NAME) $(FLAGS) $(FRAMEWORKS) $(addprefix $(PATH_LIB), $(LIB)) \
			$(addprefix $(PATH_DR), $(OBJS_DR)) $(addprefix $(PATH_EV), $(OBJS_EV)) \
			$(addprefix $(PATH_PA), $(OBJS_PA)) $(addprefix $(PATH_RA), $(OBJS_RA))

clean	:	
				rm -rf $(addprefix $(PATH_DR), $(OBJS_DR)) $(addprefix $(PATH_EV), $(OBJS_EV)) \
				$(addprefix $(PATH_PA), $(OBJS_PA)) $(addprefix $(PATH_RA), $(OBJS_RA))

fclean	:	clean
				rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re

#compiling .o with flags
$(PATH_DR)%.o		:	$(PATH_DR)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_EV)%.o		:	$(PATH_EV)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_PA)%.o		:	$(PATH_PA)%.c
			$(CC) $(FLAGS) -o $@ -c $<

$(PATH_RA)%.o		:	$(PATH_RA)%.c
			$(CC) $(FLAGS) -o $@ -c $<
