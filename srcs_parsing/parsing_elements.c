/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 18:04:46 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/25 11:20:41 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Fill the 2 ints of the tab par->reso with one line of the map (Key : "R ")
*/
int		parse_reso(t_pars *par, char *line)
{
	int		i;
	char	**tmp;

	i = 0;
	if (par->reso[0] != -1 || par->reso[1] != -1) //if already something in the tab
		error_msg("File .cub, resolution : multiple keys 'R'\n", par, line);
	if (!(tmp = ft_split(line, ' '))) //return a **char ended by a NULL ptr
		return (-1); //we only use the **char now, line will be free in struct_fill
	while (tmp[i])
		i++; //i should value 3 after this loop : R, reso x, reso y
	if (i != 3 || !ft_strisdigit(tmp[1]) || !ft_strisdigit(tmp[2]))
	{
		free_split(tmp);
		error_msg("File .cub, resolution : 3 arguments are waited\n"
		"The key (R), reso X and Y (those last two only in numbers)\n", par, line);
	}
	if (ft_strlen(tmp[1]) > (size_t)5) //reso max possible value will never be > at 99999
		par->reso[0] = RESO_MAX_X;
	else
		par->reso[0] = (i = ft_atoi(tmp[1])) > RESO_MAX_X ? RESO_MAX_X : i;
	if (ft_strlen(tmp[2]) > (size_t)5) //allow to secure the atoi if a to huge number is set for the reso
		par->reso[1] = RESO_MAX_Y;
	else
		par->reso[1] = (i = ft_atoi(tmp[2])) > RESO_MAX_Y ? RESO_MAX_Y : i;
	free_split(tmp);
	return (1);
}

/*
** Check for key 'F' and key 'C' if the format 'nb,nb,nb' is respected.
*/
int		check_format_rgb(char *line)
{
	int i;

	i = 1; //we start after the key (either F or C)
	while (line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i++])) //RGB couple should start by a digit
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i++] != ',' || !ft_isdigit(line[i++])) // ',' should be follow by a number
		return (0);
	while (ft_isdigit(line[i]))
		i++;
	if (line[i++] != ',' || !ft_isdigit(line[i++]))
		return (0);
	return (1);
}

/*
** Fill the 3 ints of the tab par->flo_rgb with one line of the map (Key : "F ")
*/
int		parse_flo_rgb(t_pars *par, char *line)
{
	int i;
	char **tmp;

	i = 0;
	if (par->flo_rgb != -1) //if already something in the tab
		error_msg("File .cub, colors : multiple keys 'F'\n", par, line);
	if (!check_format_rgb(line))
		error_msg("File .cub, colors : (F) RGB couple should respect format 'nb,nb,nb'\n", par, line);
	ft_replace_char(line, ' ', ',');
	if (!(tmp = ft_split(line, ' '))) //return a **char ended by a NULL ptr
		return (-1); //we only use the **char now, line will be free in struct_fill
	while (tmp[i])
		i++; //i should value 4 after this loop : F, and RGB values
	if (i != 4 || !ft_strisdigit(tmp[1]) || !ft_strisdigit(tmp[2]) || !ft_strisdigit(tmp[3])
		|| ft_strlen(tmp[1]) > (size_t)3 || ft_strlen(tmp[2]) > (size_t)3 //RGB color will never be > 255 (3 numbers)
		|| ft_strlen(tmp[3]) > (size_t)3 || ((i = ft_atoi(tmp[1])) > 255)
		|| ((i = ft_atoi(tmp[2])) > 255) || ((i = ft_atoi(tmp[3])) > 255))
	{
		free_split(tmp);
		error_msg("File .cub, colors : 4 arguments are waited for the floor\n"
		"The key (F), R, G and B values (those last three between 000 and 255)\n", par, line);
	}
	*((unsigned char *)(&par->flo_rgb)) = (unsigned char)ft_atoi(tmp[1]); //stocking each RGB color in an int, byte per byte
	*((unsigned char *)(&par->flo_rgb) + 1) = (unsigned char)ft_atoi(tmp[2]);
	*((unsigned char *)(&par->flo_rgb) + 2) = (unsigned char)ft_atoi(tmp[3]);
	*((unsigned char *)(&par->flo_rgb) + 3) = (unsigned char)0;
	free_split(tmp);
	return (1);
}

/*
** Fill the 3 ints of the tab par->sky_rgb with one line of the map (Key : "C ")
*/
int		parse_sky_rgb(t_pars *par, char *line)
{
	int i;
	char **tmp;

	i = 0;
	if (par->sky_rgb != -1) //if already something in the tab
		error_msg("File .cub, colors : multiple keys 'C'.\n", par, line);
	if (!check_format_rgb(line))
		error_msg("File .cub, colors : (C) RGB couple should respect format 'nb,nb,nb'\n", par, line);
	ft_replace_char(line, ' ', ',');
	if (!(tmp = ft_split(line, ' '))) //return a **char ended by a NULL ptr
		return (-1); //we only use the **char now, line will be free in struct_fill
	while (tmp[i])
		i++; //i should value 4 after this loop : C, and RGB values
	if (i != 4 || !ft_strisdigit(tmp[1]) || !ft_strisdigit(tmp[2]) || !ft_strisdigit(tmp[3]) //only diggit so can't be < 0
		|| ft_strlen(tmp[1]) > (size_t)3 || ft_strlen(tmp[2]) > (size_t)3 //protect from sending a to huge number to atoi
		|| ft_strlen(tmp[3]) > (size_t)3 || ((i = ft_atoi(tmp[1])) > 255) //RGB color must be between 0 and 255
		|| ((i = ft_atoi(tmp[2])) > 255) || ((i = ft_atoi(tmp[3])) > 255))
	{
		free_split(tmp);
		error_msg("File .cub, colors : 4 arguments are waited for the sky\n"
		"The key (C), R, G and B values (those last three between 000 and 255)\n", par, line);
	}
	*((unsigned char *)(&par->sky_rgb)) = (unsigned char)ft_atoi(tmp[1]); //stocking each RGB color in an int, byte per byte
	*((unsigned char *)(&par->sky_rgb) + 1) = (unsigned char)ft_atoi(tmp[2]);
	*((unsigned char *)(&par->sky_rgb) + 2) = (unsigned char)ft_atoi(tmp[3]);
	*((unsigned char *)(&par->sky_rgb) + 3) = (unsigned char)0;
	free_split(tmp);
	return (1);
}

/*
** Parse one line of the map and malloc the path of textures/sprites on *par.
** (Key : "NO ", "SO ", "WE ", "EA ", "S ", "FB ", "CB ", "DB ").
*/
int		parse_path(t_pars *par, char **path, char *line)
{
	int i;
	char **tmp;

	i = 0;
	if (*path) //if not NULL, we already have treated this key
		error_msg("File .cub, path : multiple same keys\n", par, line);
	if (!(tmp = ft_split(line, ' '))) //return a **char ended by a NULL ptr
		return (-1); //we only use the **char now, line will be free in struct_fill
	while (tmp[i])
		i++; //i should value 2 after this loop : the key and the path
	if (i != 2) 
	{
		free_split(tmp);
		error_msg("File .cub, path : two arguments are waited\n"
		"The key, and then the path\n", par, line);
	}
	*path = tmp[1]; //path is one of the ptr contained inside the struct t_pars *par
	free(tmp[0]);
	free(tmp);
	return (1);
}
