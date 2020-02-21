/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:16:20 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/21 10:48:35 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

void print_struct(t_cube *par)
{
	int i;

	i = 0;
	printf("reso = [%d][%d]\n", par->reso[0], par->reso[1]);
	printf("path no = |%s|\n", par->path_no);
	printf("path so = |%s|\n", par->path_so);
	printf("path we = |%s|\n", par->path_we);
	printf("path ea = |%s|\n", par->path_ea);
	printf("path sp = |%s|\n", par->path_sp);
	printf("sky_rgb = [%d][%d][%d]\n", par->sky_rgb[0], par->sky_rgb[1], par->sky_rgb[2]);
	printf("flor_rgb = [%d][%d][%d]\n", par->flo_rgb[0], par->flo_rgb[1], par->flo_rgb[2]);
	if (!par->map)
		printf("map inexistante\n");
	else
	{
		while (par->map[i])
			printf("|%s|\n", par->map[i++]);
	}
}

int main(int ac, char **av)
{
	char *line;
	t_cube par;
	line = NULL;
	
    check_arg(ac, av);
	struct_init(&par);
	if ((par.fd = open(av[1], O_RDONLY)) == -1)
		error_msg("Error\nArguments : incorrect file\n", &par, NULL);
	parsing(&par);
	print_struct(&par);
	struct_free(&par);
    close(par.fd);
	// system("leaks a.out");
    return (0);
}
