/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldelena <fldelena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:44:41 by fldelena          #+#    #+#             */
/*   Updated: 2021/01/18 18:53:00 by fldelena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_full_line(char *rmndr)
{
	int				i;
	char			*fullline;

	i = 0;
	if (!rmndr)
		return (0);
	while (rmndr[i] && rmndr[i] != '\n')
		i++;
	if (!(fullline = (char *)malloc(sizeof(char) * (i + 1))))
		return (0);
	fullline[i] = '\0';
	while (--i >= 0)
		fullline[i] = rmndr[i];
	return (fullline);
}

char	*ft_remainder(char *str)
{
	char	*remainder;
	int		i;
	int		k;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	if (!(remainder = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1))))
		return (0);
	k = i;
	while (str[++i])
		remainder[i - (k + 1)] = str[i];
	remainder[i - (k + 1)] = '\0';
	free(str);
	return (remainder);
}

int		get_next_line(int fd, char **line)
{
	static char		*str;
	char			*buf;
	int				endread;

	endread = 1;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((endread != 0) && !ft_endline(str))
	{
		endread = read(fd, buf, BUFFER_SIZE);
		if (endread == -1)
		{
			free(buf);
			return (-1);
		}
		buf[endread] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	*line = ft_full_line(str);
	str = ft_remainder(str);
	return ((!str) ? 0 : 1);
}
