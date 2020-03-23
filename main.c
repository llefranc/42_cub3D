/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:16:20 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/23 11:27:09 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

void	print_map(int **map)
{
	int i = 0;
	int j;

	while (map[i])
	{
		j = -1;
		printf("|");
		while (map[i][++j] != -2)
		{
			if (map[i][j] == -1)
				printf(" ");
			else if (map[i][j] == NORTH)
				printf("N");
			else if (map[i][j] == SOUTH)
				printf("S");
			else if (map[i][j] == EAST)
				printf("E");
			else if (map[i][j] == WEST)
				printf("W");
			else
				printf("%d", map[i][j]);
		}
		printf("|\n");
		i++;
	}
}

void	print_struct(t_pars *par)
{
	int i;

	i = 0;
	printf("reso = [%f][%f]\n", par->reso[0], par->reso[1]);
	printf("path no = |%s|\n", par->path_no);
	printf("path so = |%s|\n", par->path_so);
	printf("path we = |%s|\n", par->path_we);
	printf("path ea = |%s|\n", par->path_ea);
	printf("path sp = |%s|\n", par->path_sp);
	printf("sky_rgb = color = [%d] RGB[%d][%d][%d]\n", par->sky_rgb,*(unsigned char *)(&par->sky_rgb), 
			*((unsigned char *)(&par->sky_rgb) + 1), *((unsigned char *)(&par->sky_rgb) + 2));
	printf("flor_rgb = color = [%d] RGB[%d][%d][%d]\n", par->flo_rgb,*(unsigned char *)(&par->flo_rgb),
			*((unsigned char *)(&par->flo_rgb) + 1), *((unsigned char *)(&par->flo_rgb) + 2));
	if (!par->map)
		printf("map inexistante\n");
	else
		print_map(par->map);
}

int main(int ac, char **av)
{
	char *line;
	t_pars par;
	line = NULL;
	
    check_arg(ac, av);
	struct_init_par(&par);
	if ((par.fd = open(av[1], O_RDONLY)) == -1)
		error_msg("Error\nArguments : incorrect file\n", &par, NULL);
	parsing(&par);
	// print_struct(&par);
	drawing(&par);
	struct_free(&par);
    return (0);
}
