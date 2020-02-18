/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:49:53 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/18 16:10:10 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Print the error msg (= str), and if par exist free each elements of the 
** structure filled with map parameters. Free also one char * (line), send NULL
** into it if there is nothing to free. Then close the file descriptor and exit.
*/
int		error_msg(char *str, t_cube *par, char *line)
{
    perror(str);
	if (par)
		struct_free(par);
	free(line);
	// line = NULL; //a enlever
	// struct_init(par);//a enlever
	// system("leaks a.out");//a enlever
	exit(EXIT_FAILURE);
}

/*
** Check if there is only one argument (the map) and if the extension of the
** map file is correct. Call error_msg in case of error.
*/
int     check_arg(int ac, char **av)
{
    int i;

    i = 0;
    if (ac < 2)
        error_msg("Error\nArguments : no file, enter it with the first argument\n", NULL, NULL);
    else if (ac > 2)
        error_msg("Error\nArguments : too many arguments, enter only the map file\n", NULL, NULL);
    else
    {
        while (av[1][i])
            i++;
        i -= 4;
        if (!ft_strcmp(&av[1][i], ".cub"))
            return (1);
        error_msg("Error\nArguments : file map must end by \".cub\"\n", NULL, NULL);
    }
    return (-1);
}


/*
** Return 1 if the string is only made of digits, otherwise return 0.
*/
int		ft_strisdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}

/*
** Free properly the **char created by a split.
*/
void	free_split(char **split)
{
	int i;

	i = 0;
	while (split[i]) //ft_split end the **char by a NULL ptr
		free(split[i++]);
	free(split);
}
