/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:16:20 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/03/04 17:58:34 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube3d.h"

void print_struct(t_pars *par)
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
	{
		while (par->map[i])
			printf("|%s|\n", par->map[i++]);
	}
}

//envoyer 0 ou 1 dan s player en fonction de si on veut l'afficher (= 1).
void	print_map(t_rcast cam, int player)
{
	int line = 0;
	int row;

	while (line < cam.nb_lines)
	{
		row = 0;
		while (row < cam.nb_rows)
		{
			if (player && (int)cam.x == row && (int)cam.y == line)
				ft_printf("P");
			else
				ft_printf("%d", (cam.map)[line][row]);
			row++;
		}
		ft_printf("\n");
		line++;
	}
}

//gerer les maps non carres
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
