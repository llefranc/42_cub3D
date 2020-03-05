/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:41:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/05 14:09:29 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Add one extra *int to **int par->map, and add the new line of the map
** at the end. Terminate **int par->map by NULL. Return the new **int and
** NULL if something failed.
*/
int		**add_map_line(t_pars *par, int *line)
{
	int i;
	int **tmp;
	
	i = 0;
	if (!par->map) //if it's the first line of the map
	{
		if (!(par->map = malloc(sizeof(int *) * 2))) //+2 for new line and NULL terminating
			return (NULL);
		par->map[0] = line;
		par->map[1] = NULL;
	}
	else
	{
		tmp = par->map;
		while (par->map[i])
			i++;
		if (!(par->map = malloc(sizeof(int *) * (i + 2)))) //+2 for new line and NULL terminating
		{
			par->map = tmp; //we set par->map on the previous **int for freeing it correctly after
			return (NULL);
		}
		par->map[i] = line;
		par->map[i + 1] = NULL;
		while (--i >= 0) //we copy the previous **int in the new one
			par->map[i] = tmp[i];
		free(tmp);
	}
	return (par->map);
}

/*
** Take a *char line of the map and return a new int_line who was mallocated.
** The new line can contain : 0, 1, 2, 30 (= N), 35 (= S), 21 (= E), 39 (= W),
** and -1 for spaces and one and only -2 at the end of the int_line for
** terminating it like a '\0' for a *char.
*/
int		*convert_int_line(char *line)
{
	int		i;
	int		*int_line;

	i = -1;
	if (!(int_line = malloc(sizeof(*int_line) * (ft_strlen(line) + 1))))
		return (NULL);
	while (line[++i])
	{
		if (line[i] == ' ')
			int_line[i] = -1;
		else
			int_line[i] = line[i] - '0';	//NSEW will value respectively 30, 35, 21, 39
	}										//Those values are defined (NORTH, SOUTH, EAST, WEST)
	int_line[i] = -2; //terminate the int_line, like a '\0' for a *char
	return (int_line);
}

/*
** Trim the spaces of line by creating a new char *trim_line, then do a realloc
** of size + 1 on the **char par->map, add the new trim_line at the end and
** finished the **char par->map by a NULL *ptr.
*/
int		parse_map(t_pars *par, char *line)
{
	int i;
	int *int_line;

	i = 0;
	if (!(int_line = convert_int_line(line))) //create a new *int_line with all the values converted
		error_msg("Malloc failed\n", par, line);
	if (!(par->map = add_map_line(par, int_line))) //realloc par-map with size + 1 and add int_line at the end
	{
		free(int_line);
		error_msg("Malloc failed\n", par, line);
	}
	return (1);
}
