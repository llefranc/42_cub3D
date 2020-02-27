/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:41:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/27 18:47:36 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Create and return a new string without the char 'c'. If something failed,
** return NULL. Do not free the previous str. 
*/
char	*trim_char(char *str, char c)
{
	int i;
	int len;
	char *str_trim;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i++] != c)
			len++; //lenght of str without char c
	}
	if (!(str_trim = malloc(len + 1)))
		return (NULL);
	while (i >= 0)
	{
		if (str[i] != c) //if not char c, we copy str[i] in new string
			str_trim[len--] = str[i];
		i--;
	}
	return (str_trim);
}

/*
** Add one extra *char to **char par->map, and add the new line of the map
** at the end. Terminate **char par->map by NULL. Return the new **char and
** NULL if something failed.
*/
char	**add_map_line(t_pars *par, char *line)
{
	int i;
	char **tmp;
	
	i = 0;
	if (!par->map) //if it's the first line of the map
	{
		if (!(par->map = malloc(sizeof(char *) * 2))) //+2 for new line and NULL terminating
			return (NULL);
		par->map[1] = NULL;
		par->map[0] = line;
	}
	else
	{
		while (par->map[i])
			i++;
		tmp = par->map;
		if (!(par->map = malloc(sizeof(char *) * (i + 2)))) //+2 for new line and NULL terminating
		{
			par->map = tmp; //we set par->map on the previous **char for freeing it correctly
			return (NULL);
		}
		par->map[i + 1] = NULL;
		par->map[i] = line;
		while (--i >= 0) //we copy the previous **char in the new one
			par->map[i] = tmp[i];
		free(tmp);
	}
	return (par->map);
}

/*
** Trim the spaces of line by creating a new char *trim_line, then do a realloc
** of size + 1 on the **char par->map, add the new trim_line at the end and
** finished the **char par->map by a NULL *ptr.
*/
int		parse_map(t_pars *par, char *line)
{
	int i;
	char *trim_line;

	i = 0;
	if (!(trim_line = trim_char(line, ' '))) //create a new line without spaces
		error_msg("Malloc failed\n", par, line);
	if (!(par->map = add_map_line(par, trim_line))) //realloc par-map with size + 1 and add trim_line at the end
	{
		free(line);
		error_msg("Malloc failed\n", par, trim_line);
	}
	return (1);
}

/*
** Check if all the characters of one line of the map are corrects, and return
** the number of times player position was detected ("NSWE" characters).
*/
int		line_check(t_pars *par, char *line_map)
{
	int i;
	int pos;

	i = 0;
	pos = 0;
	while (line_map[i])
	{
		if (!ft_strchr("012NSWE", line_map[i]))
			error_msg("File .cub, map : must only contains "
			"'012NSWE' characters and/or spaces\n", par, NULL);
		if (ft_strchr("NSWE", line_map[i++]))
			pos++;
	}
	return (pos);
}

/*
** Compare the actual line of the map and the previous one to see if they're
** surrunded by walls.
*/
void	walls_check(t_pars *par, char *actual, char *previous)
{
	long i;
	long j;

	i = 0;
	(void)par;
	i = ft_strlen(actual) - ft_strlen(previous);
	if (i < 0) //actual line is smaller than previous
	{
		j = ft_strlen(previous) - 1; //we start at the end of previous
		while (i <= 0)
			if (previous[j + i++] != '1') //and compare until we reach the size of actual
				error_msg("File .cub, map : must only be"
				" surrunded by walls ('1')\n", par, NULL);
	}
	else //actual is equal or taller than previous
	{
		j = ft_strlen(previous) - 1;
		while (i >= 0) //if actual is equal to previous, we check only the last charac of actual
			if (actual[j + i--] != '1') //we compare from the end of actual until we reach size of previous
				error_msg("File .cub, map : must only be"
				" surrunded by walls ('1')\n", par, NULL);
	}
}

/*
** Check if the map is filled with authorized characters "012NSWE", if the
** player position is correct and if the map is surrunded by walls.
*/
int		map_check(t_pars *par)
{
	long i;
	long j;
	int	pos;

	i = 0;
	j = 0;
	pos = 0;
	while (par->map[i]) //if non-authorized characters in the map (012NSWE), error
		pos += line_check(par, par->map[i++]); //return nb times player position is detected in a line
	!pos ? error_msg("File .cub, map : no player position\n", par, NULL) : 0;
	pos > 1 ? error_msg("File .cub, map : several player positions\n", par , NULL) : 0;
	while (par->map[0][j]) //check first line of the map
		if (par->map[0][j++] != '1')
			error_msg("File .cub, map : first line must be only '1' and/or spaces\n", par, NULL);
	j = 0;
	while (par->map[i - 1][j]) //check first line of the map
		if (par->map[i - 1][j++] != '1')
			error_msg("File .cub, map : last line must be only '1' and/or spaces\n", par, NULL);
	while (--i > 0) //checking all the map from the end to the beginning
		walls_check(par, par->map[i], par->map[i - 1]); //check if map surrunded by walls
	return (1);
}
