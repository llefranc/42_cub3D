/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 14:53:51 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/04/07 10:57:33 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

/*
** Free properly parsing and sprites structs, then destroy all images
** previously loaded, print a message if needed and exit.
*/
void	exit_with_sucess(t_mlx *mlx, const char *msg)
{
	if (mlx->par)
		struct_free(mlx->par); //also close file descriptor
	if (mlx->spri)
		free_sprite_struct(mlx->spri);
	destroy_all_images(mlx, &mlx->img);
	ft_printf("%s", msg);
	exit(EXIT_SUCCESS);
}

/*
** Take an int from screen image (a tab of int). In this one each int represent
** a color, and in each int : octet 1 is 0, octect 2 is red, 3 green, 4 blue.
** Due to little endian octets are in the reverse order. We're then copying
** those 3 octets in our bmp image.
*/
void	put_3_octets_in_str_img(char *int_to_fill, int *i, int value)
{
	*((unsigned char *)int_to_fill) = *(unsigned char *)&value; //blue
	*((unsigned char *)int_to_fill + 1) = *((unsigned char *)&value + 1); //green
	*((unsigned char *)int_to_fill + 2) = *((unsigned char *)&value + 2); //red
	*i += 3; //i is the number of octets copied in our  bmp image
}

/*
** Allows to copy one int in our BMP image.
*/
void	put_4_octets_in_str_img(int *int_to_fill, int *i, int value)
{
	*int_to_fill = value;
	*i += 4;  //i is the number of octets copied in our  bmp image
}

/*
** Fills a char *str with all headers information for a BMP image. The size of
** the header is 54 octets.
*/
int		fill_bmp_header_info(t_mlx *mlx, char *img_str, int i, int size_str_img)
{
	img_str[i++] = 0x42; //BM characters, to indicate it's a bitmap image
	img_str[i++] = 0x4D;
	put_4_octets_in_str_img((int *)&img_str[i], &i, size_str_img); //size of the img (including padding bytes)
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x0); //always zero (reserved)
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x36); //adress where starts img file (54 octets = header size)
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x28); //size of the second part of header (40 octets)
	put_4_octets_in_str_img((int *)&img_str[i], &i, (int)mlx->par->reso[0]); //width
	put_4_octets_in_str_img((int *)&img_str[i], &i, (int)mlx->par->reso[1]); //height
	img_str[i++] = 0x1; //number of plan (1)
	img_str[i++] = 0x0;
	img_str[i++] = 0x18; //bits per pixel (24)
	img_str[i++] = 0x0;
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x0); //compress method (0 : no compress)
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x0); //size of image after compressed, usefull when compress method used
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x0); //XPixelsPerMeter, will be used by applications
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x0); //YPixelsPerMeter
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x0); //palette color, don't need when 24 bits bmp
	put_4_octets_in_str_img((int *)&img_str[i], &i, 0x0); //palette color	
	return (i); //should value 54
}

/*
** Copies each pixel of screen image into the bmp image, but only the 3 RGB
** bytes. If at the end of one line of BMP img the total of bytes copied is
** not divisible by 4, the function will add 1/2/3 padding bytes with a value
** of 0. Also, BMP image requires to copy lines in the reverse order, from
** bottom to top, but still from left to right.
*/
void	fill_bmp_with_data_img(t_mlx *mlx, char *img_str, int i, int padding_byte)
{
	int		row;
	int		line;
	int		j; //for moving in screen img
	int		line_img;

	line = -1;
	line_img = (int)mlx->par->reso[1] - 1; //we're starting from the bottom left corner of image
	while (++line < (int)mlx->par->reso[1])
	{
		j = 0;
		row = -1;
		while (++row < (int)mlx->par->reso[0]) //copying colors from screen image (in reverse order for lines)
			put_3_octets_in_str_img(&img_str[i], &i, mlx->addr.screen[j++ 
					+ line_img * mlx->info.screen[SIZE_LINE]]); 
		line_img--; //copying from bottom to top
		padding_byte == 3 ? put_3_octets_in_str_img(&img_str[i], &i, 0) : 0;
		if (padding_byte == 2)	
		{												//adding padding bytes at the end of each
			img_str[i++] = 0x0;							//line if the total of bytes in one line
			img_str[i++] = 0x0;							//is not divisible by 4
		}
		padding_byte == 1 ? img_str[i++] = 0x0 : 0;
	}
}

/*
** Opens and creates if not existing a file to save the first image created by
** the raycasting as BMP. Malloc a char *str of the size of header info (54
** bytes) + image size, fills this char * and write it into the file. Then
** exit with sucess message.
*/
void	save_image_as_bmp(t_mlx *mlx)
{
	int		fd;
	int		padding_byte; //each line of img must be divisible by 4. Otherwise need to add padding bytes
	int		i;
	char	*img_str;
	int		size_str_img;

	i = 0;
	padding_byte = 4 - (int)mlx->par->reso[0] % 4;	//if one line of img is 5 pixels, will be 15 bytes
	padding_byte == 4 ? padding_byte = 0 : 0;		//(5 x 3 for RGB couple) so need 1 padding byte
	//size of file, 54 is the header size. Reso x3 because 3 values per pixel for 
	//RGB couple + rows of padding bytes if necesseraly
	size_str_img = 54 + ((int)mlx->par->reso[0] * (int)mlx->par->reso[1] * 3)
			+ padding_byte * (int)mlx->par->reso[1];
	fd = open("save.bmp", O_RDWR | O_CREAT, 0644); //0644 to create a file with 'read' and 'write' mode (cf chmod)
	if (fd == -1)
		error_msg_destroy_img("File : failed to create save file\n", mlx);
	if (!(img_str = malloc(size_str_img + 1))) //+1 for \0
		error_msg_destroy_img("Malloc failed\n", mlx);
	img_str[size_str_img] = '\0';
	i = fill_bmp_header_info(mlx, img_str, i, size_str_img); //fills 54 first bytes (header with info)
	fill_bmp_with_data_img(mlx, img_str, i, padding_byte); //copies the pixels colors from screen image
	write(fd, img_str, size_str_img); //write all the *char into the file (header + data)
	free(img_str);
	exit_with_sucess(mlx, "First image saved as BMP with sucess\n");
}