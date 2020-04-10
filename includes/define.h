/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 12:29:52 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/08 11:08:45 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		DEFINE_H
# define	DEFINE_H

# include	"cube3d.h"

//resolution values
# define	RESO_MAX_X			2560
# define	RESO_MAX_Y			1440

//keys values
# define	RESO				1
# define	P_NORTH				2
# define	P_SOUTH				3
# define	P_EAST				4
# define	P_WEST				5
# define	P_SPRIT				6
# define	P_B_FLOOR			7
# define	P_B_SKY				8
# define	P_B_DOOR			9
# define	FLO_RGB				10
# define	SKY_RGB				11
# define	MAP_LINE			12

//values for N/W/E/S - 48 (ASCII values)
# define	NORTH				30
# define	SOUTH				35
# define	EAST				21
# define	WEST				39

//raycasting constants
# define	WALL_SIZE			64			//height of wall
# define	MOVE_SIZE			0.065
# define	TIME_MOVE			0.015
# define	ROTA_SIZE			2.5
# define	M_ROTA_SIZE			0.75
# define	FOV					50			//field of view

//angle in degrees
# define	V_EAST				0
# define	V_NORTH				90
# define	V_WEST				180
# define	V_SOUTH				270

//usefull to convert degrees <=> radians
# define	TO_DEG				180.0 / M_PI
# define	TO_RAD				M_PI / 180.0

//usefull for t_info structure, allow to move in the tab of 3 ints
//and selects the parameter expected
# define	BITS_PER_PIX		0
# define	SIZE_LINE			1
# define	ENDIAN				2
# define	WIDTH				3
# define	HEIGHT				4

//types of doors
# define	DOOR				2
# define	SECRETDOOR			3

//types of sprite
# define	SP_GUARD			4
# define	SP_TREE				5
# define	SP_ARMOR			6
# define	SP_HEALTH			7
# define	SP_AMMO				8
# define	SP_FLAG				9
# define	SP_HUD				10
# define	SP_LIFEBAR			11
# define	SP_GUNS				12
# define	SP_NUMBERS			13
# define	SP_FONT				14

//width (in pixel) of sprites on screen for sprite collision
# define	GUARD_SIZE			24
# define	TREE_SIZE			20
# define	ARMOR_SIZE			30
# define	HEALTH_SIZE			40
# define	AMMO_SIZE			40
# define	FLAG_SIZE			16

//sprite's background color that we're not printing
# define	INV_COLOR			9961608

//texture's first pixel position in images (L = line, R = row)
# define	T1_NORTH_L			0			//level 1
# define	T1_NORTH_R			64
# define	T1_SOUTH_L			0
# define	T1_SOUTH_R			320
# define	T1_EAST_L			64
# define	T1_EAST_R			64
# define	T1_WEST_L			64
# define	T1_WEST_R			320
# define	T2_NORTH_L			704			//level 2
# define	T2_NORTH_R			192
# define	T2_SOUTH_L			704
# define	T2_SOUTH_R			192
# define	T2_EAST_L			704
# define	T2_EAST_R			192
# define	T2_WEST_L			704
# define	T2_WEST_R			192
# define	T3_NORTH_L			832			//level 3
# define	T3_NORTH_R			64
# define	T3_SOUTH_L			832
# define	T3_SOUTH_R			64
# define	T3_EAST_L			832
# define	T3_EAST_R			64
# define	T3_WEST_L			832
# define	T3_WEST_R			64
# define	T_FLOOR_L			192			//floor
# define	T_FLOOR_R			256

//sprite's first pixel position in images (L = line, R = row)
# define	LIFE_RED_IMG_L		0
# define	LIFE_RED_IMG_R		37
# define	LIFE_EMPTY_IMG_L	24
# define	LIFE_EMPTY_IMG_R	37
# define	GUNS_IMG_L			65
# define	GUNS_IMG_R			65
# define	NUMBER_IMG_L		41
# define	NUMBER_IMG_R		228
# define	HEART_IMG_L			10
# define	HEART_IMG_R			2

//guards' sprites first pixel position in image (L = line, R = row)
# define	G_BASIC_L			0
# define	G_BASIC_R			0
# define	G_DETECT_L			390
# define	G_DETECT_R			0
# define	G_DEAD_L			325
# define	G_DEAD1_R			0
# define	G_DEAD2_R			65
# define	G_DEAD3_R			130
# define	G_DEAD4_R			195
# define	G_DEAD5_R			260
# define	G_SHOOT_L			390
# define	G_SHOOT1_R			65
# define	G_SHOOT2_R			130

//size of sprites in percent of screen height / screen width
# define	HUD_SIZE_H			1.0 / 6.0
# define	LIFE_SIZE_H			0.05
# define	LIFE_SIZE_W			1.0 / 6.0
# define	GUNS_SIZE_H			0.7
# define	GUNS_SIZE_W			0.5
# define	NUMBER_SIZE_H		0.08
# define	NUMBER_SIZE_W		0.03
# define	HEART_SIZE_H		0.05
# define	HEART_SIZE_W		0.025
# define	FONT1_SIZE_H		0.085
# define	FONT1_SIZE_W		0.05
# define	FONT2_SIZE_H		0.1			//for deaths screens
# define	FONT2_SIZE_W		0.06

//sprite's position on screen
# define	LIFE_SCREEN_L		0.91
# define	LIFE_SCREEN_R		0.125
# define	GUNS_SCREEN_L		0.135
# define	GUNS_SCREEN_R		0.25
# define	NUMBER_SCREEN_L		0.895
# define	N_LEVEL_SCREEN_R	0.05
# define	N_LIFE1_SCREEN_R	0.52
# define	N_LIFE2_SCREEN_R	0.55
# define	N_LIFE3_SCREEN_R	0.58
# define	N_AMMO1_SCREEN_R	0.68
# define	N_AMMO2_SCREEN_R	0.71
# define	HEART_SCREEN_L		0.92
# define	HEART1_SCREEN_R		0.315
# define	HEART2_SCREEN_R		0.345
# define	HEART3_SCREEN_R		0.375
# define	FONT1_SCREEN_L		0.3			//for level menu
# define	FONT1_SCREEN_R		0.08
# define	FONT2_SCREEN_L		0.45		//for deaths screens
# define	FONT2_SCREEN_R		0.28

//size of one sprite (in pixel) contained inside an image of several sprites
# define	LIFE_PIX_H			21
# define	LIFE_PIX_W			332
# define	GUNS_PIX_H			64
# define	GUNS_PIX_W			64
# define	NUMBER_PIX_H		16
# define	NUMBER_PIX_W		8
# define	HEART_PIX_H			27
# define	HEART_PIX_W			32
# define	FONT_PIX_H			40
# define	FONT_PIX_W			24

//guard parameters
# define	NOT_SEEING			0
# define	DETECTING_PLAYER	1
# define	DYING				2
# define	DEAD				3

//player's informations
# define	AMMO_START			20
# define	FULL_AMMO			99
# define	FULL_LIFE			100
# define	NB_LIFE_START		3

//interactions with player
# define	GAIN_HEALTH			20
# define	GAIN_AMMO			5

#endif