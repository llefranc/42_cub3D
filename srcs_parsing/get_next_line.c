/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:52:10 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/02/12 20:31:22 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

char	*fill_line(char buff[], char **line)
{
	char	*str;
	char	*tmp;
	int		len;
	int		i;

	len = 0;
	while (buff[len] && buff[len] != '\n')
		len++;
	if (!(str = malloc(len + 1)))
		return (NULL);
	str[len] = '\0';
	i = -1;
	while (++i < len)
		str[i] = buff[i];
	ft_strlcpy(buff, buff + len + 1, ft_strlen(buff) - (size_t)(len));
	tmp = *line;
	if (!(*line = ft_strjoin(*line, str)))
		return (NULL);
	free(tmp);
	free(str);
	return (*line);
}

int     get_next_line(int fd, char **line)
{
    static char	buff[BUFF_GNL + 1];
    int			ret;
	char		*tmp;

    if (!line | (read(fd, buff, 0) == -1))
    	return (-1);
	*line = NULL;
	ret = 1;
    while (!ft_strchr(buff, '\n') && ret)
	{
		tmp = *line;
		*line = ft_strjoin(*line, buff);
		free(tmp);
		ret = read(fd, buff, BUFF_GNL);
	}
	if (!ret && !ft_strchr(buff, '\n'))
		return (0);
	if (!(*line = fill_line(buff, line)))
		return (-1);
    return (1);
}