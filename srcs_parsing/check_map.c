/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:08:50 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/19 11:29:25 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Return the number of times player position was detected ("NSWE" characters).
*/
int		pos_player_check(int *line_map)
{
	int		i;
	int		pos;

	i = -1;
	pos = 0;
	while (line_map[++i] != -2)
	{
		if (line_map[i] == NORTH || line_map[i] == SOUTH ||
			line_map[i] == EAST || line_map[i] == WEST)
			pos++;
	}
	return (pos);
}

/*
** Check if the first and last line contains only '1' and spaces, and if at
** least one wall is present.
*/
int		first_last_line_check(t_pars *par, int *line)
{
	int 	i;
	int		wall_present;

	i = -1;
	wall_present = 0;
	while (line[++i] != -2)
	{
		if (line[i] != 1 && line[i] != -1) //-1 for spaces
			return (0);
		if (line[i] == 1)
			wall_present = 1; //boolean to indicate that there is at least one wall
	}
	if (!wall_present)
		error_msg_map("File .cub, map : First line and last line"
		" must contains at least one wall\n", par, line);
	return (1);
}

/*
** Return the len of one line of the map. The line must be terminated by -2.
*/
int		len_line_map(int *line)
{
	int		i;

	i = 0;
	while (line[i] != -2)
		i++;
	return (i);
}

/*
** Exit and print an error is one line of the map is not terminated by a 1.
*/
void	line_is_ended_by_wall(t_pars *par, int *line)
{
	if (line[len_line_map(line) - 1] != 1)
		error_msg_map("File .cub, map : each line of the map must be "
		"terminated by a wall\n", par, line);
}

/*
** Previous is taller than actual. Checking if the taller part of previous is
** made only of 1 and spaces.
*/
void	walls_check_previous(t_pars *par, int i, int *previous)
{
	long	j;

	j = len_line_map(previous) - 1; //we start at the end of previous
		i--;
	while (++i <= 0)
		if (previous[j + i] != 1 && previous[j + i] != -1)	//and compare until we reach
			error_msg_map("File .cub, map : must only be"	//the size of actual
			" surrunded by walls ('1')\n", par, previous);
}

/*
** Actual is taller than previous. Checking if the taller part of actual is
** made only of 1 and spaces.
*/
void	walls_check_actual(t_pars *par, int i, int *actual, int *previous)
{
	long	j;

	j = len_line_map(previous) - 1;
	i++;
	while (--i >= 0) //if actual is equal to previous, we check only the last charac of actual
		if (actual[j + i] != 1 && actual[j + i] != -1)		//we compare from the end of actual
			error_msg_map("File .cub, map : must only be"	//until we reach size of previous
			" surrunded by walls ('1')\n", par, actual);
}

/*
** Checking if one space of actual line is surrunded by 5 walls or spaces
** (left and right on actual, up-left up and up-right on previous).
*/
void	check_spaces_actual(t_pars *par, int i, int *actual, int *previous)
{
	int		bad_charac;
	int		j;

	bad_charac = 0;
	j = len_line_map(previous) - 1; //to protect the access of previous when previous' len is < i
	if (i != 0)							//checking if wall or space left and right to actual[i]
		bad_charac += (actual[i - 1] != -1 && actual[i - 1] != 1) ? 1 : 0;
	if (actual[i + 1] != -2)
		bad_charac += (actual[i + 1] != -1 && actual[i + 1] != 1) ? 1 : 0;
	if (i != 0 && i - 1 <= j)		
		bad_charac += (previous[i - 1] != -1 && previous[i - 1] != 1) ? 1 : 0;
	if (i <= j)							//checking if wall or space up to actual[i]
		bad_charac += (previous[i] != -1 && previous[i] != 1) ? 1 : 0;
	if (i + 1 <= j)
		bad_charac += (previous[i + 1] != -1 && previous[i + 1] != 1) ? 1 : 0;
	if (bad_charac)
		error_msg_map("File .cub, map : walls are not continuous\n", par, actual);
}

/*
** Checking if one space of previous line is surrunded by 5 walls or spaces
** (left and right on previous, down-left down and down-right on actual).
*/
void	check_spaces_previous(t_pars *par, int i, int *actual, int *previous)
{
	int		bad_charac;
	int		j;

	bad_charac = 0;
	j = len_line_map(actual) - 1;
	if (i != 0)							//check if wall or space left or right to previous[i]
		bad_charac += (previous[i - 1] != -1 && previous[i - 1] != 1) ? 1 : 0;
	if (previous[i + 1] != -2)
		bad_charac += (previous[i + 1] != -1 && previous[i + 1] != 1) ? 1 : 0;
	if (i != 0 && i - 1 <= j)			//check if wall or space down to previous[i]
		bad_charac += (actual[i - 1] != -1 && actual[i - 1] != 1) ? 1 : 0;
	if (i <= j)
		bad_charac += (actual[i] != -1 && actual[i] != 1) ? 1 : 0;
	if (i + 1 <= j)
		bad_charac += (actual[i + 1] != -1 && actual[i + 1] != 1) ? 1 : 0;
	if (bad_charac)
		error_msg_map("File .cub, map : walls are not continuous\n", par, previous);
}

/*
** Compare two lines of the map (actual and previous) to see if they're
** surrunded by walls and that the player can't exit the map.
*/
void	walls_check(t_pars *par, int *actual, int *previous)
{
	long i;

	i = 0;
	line_is_ended_by_wall(par, previous); //line must be terminated by a wall
	line_is_ended_by_wall(par, actual);
	i = len_line_map(actual) - len_line_map(previous);
	if (i < 0)
		walls_check_previous(par, i, previous); //actual line is smaller than previous
	else
		walls_check_actual(par, i, actual, previous); //actual is equal or taller than previous
	i = -1;
	while (actual[++i] != -2)	//check for each space in actual line if they're
		if (actual[i] == -1)	//surrunded by space or walls on actual and previous
			check_spaces_actual(par, i, actual, previous);
	i = -1;
	while (previous[++i] != -2)	//check for each space in previous line if they're
		if (previous[i] == -1)	//surrunded by space or walls on actual and previous
			check_spaces_previous(par, i, actual, previous);
}

/*
** Check if the map is filled with authorized characters "012NSWE", if the
** player position is correct and if the map is surrunded by walls.
*/
int		map_check(t_pars *par)
{
	long	i;
	int		pos;

	i = 0;
	pos = 0;
	while (par->map[i])
	{
		pos += pos_player_check(par->map[i++]); //return nb times player position is detected in a line
		pos > 1 ? error_msg_map("File .cub, map : several player positions\n", par , par->map[i - 1]) : 0;
	}
	!pos ? error_msg("File .cub, map : no player position\n", par, NULL) : 0;
	if (!first_last_line_check(par, par->map[0]))
		error_msg_map("File .cub, map : first line must be only '1' and/or spaces\n", par, par->map[0]);
	if (!first_last_line_check(par, par->map[i - 1]))
		error_msg_map("File .cub, map : last line must be only '1' and/or spaces\n", par, par->map[i - 1]);
	while (--i > 0) 	//checking all the map from the end to the beginning
		walls_check(par, par->map[i], par->map[i - 1]); //check if map surrunded by walls
	return (1);
}
