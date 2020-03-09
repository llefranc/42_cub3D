/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:27:00 by llefranc          #+#    #+#             */
/*   Updated: 2020/03/09 13:02:28 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

/*
** La struct s_number est utilisee pour des calculs sur des chaines de
** caracteres permettant de reprensenter des gros ints.
** i et j sont les indexs permettant de se deplacer dans la chaine 1 et
** la chaine 2. s1FirD represente líndex du premier chiffre different de
** zero dans la chaine 1. Meme chose pour s2FirD mais pour la seconde chaine.
*/

typedef struct	s_number
{
	int			i;
	int			j;
	int			s1fird;
	int			s2fird;
}				t_number;

/*
-------------------------------- GET_NEXT_LINE --------------------------------
*/
int					get_next_line(int fd, char **line);

/*
--------------------------------- FT_PRINTF -----------------------------------
*/
int					ft_printf(const char *str, ...);


/*
------------------------------------ LIBFT ------------------------------------
*/
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strisdigit(char *str);
char				*ft_replace_char(char *str, char neww, char prev);
double				ft_pow(double nb, double power);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, char *src, size_t dstsize);
char				*ft_strnstr(const char *haystack,
								const char *needle, size_t len);
long				ft_atoi(const char *str);
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(const char *s, unsigned int start, size_t len);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strtrim(const char *s1, const char *set);
char				**ft_split(const char *s, char c);
void				free_split(char **split);
char				*ft_itoa(long n);
char				*ft_itoa_base(long n, const char *base);
char				*ft_itoa_buffer(long n, char *buffer);
char				*ft_itoa_buffer_uns(unsigned long n, char *buffer);
char				*ft_itoa_base_buffer_uns(unsigned long n,
									char *buf, const char *base);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
------------------------------- BIG_INT_CALC_LIB ------------------------------
*/

char			*big_int_add(char *s1, char *s2);
char			*big_int_subs(char *s1, char *s2);
char			*big_int_mult(char *s1, char *s2);
char			*big_int_pow(char *s1, unsigned int pow);
char			*big_int_div(char *s1, char *s2);
void			print_mantissa(char *str);
void			print_octet(char *str);
char			*str_bits(void *type, size_t size);
int				big_int_comp(char *s1, char *s2);
char			*big_int_reset(char *str, char signe);
char			*pow_table2(char *bigint, unsigned long valexp);

#endif
