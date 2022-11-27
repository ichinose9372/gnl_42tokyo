/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:33:00 by yichinos          #+#    #+#             */
/*   Updated: 2022/11/27 12:44:27 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

void	ft_all_free(char *buf, char**save)
{
	free(buf);
	buf = NULL;
	free(*save);
	*save = NULL;
}

char	*re_creat_save(char *save, char *line)
{
	char	*pointer_save;
	char	*tmp;

	if (save && *save == '\0')
		return (NULL);
	pointer_save = ft_strchr(save, '\n');
	if (pointer_save == NULL)
		return (NULL);
	else
	{
		tmp = ft_strdup((pointer_save + 1));
		if (!tmp)
		{
			free(line);
			line = NULL;
		}
		return (tmp);
	}
}

char	*create_line(char *save)
{
	char	*line;
	size_t	len;

	len = 0;
	if (*save == '\0')
		return (NULL);
	while (save[len] != '\n' && save[len] != '\0')
		len++;
	line = malloc(sizeof(char) * (len + 2));
	if (line == NULL)
		return (NULL);
	len = 0;
	while (save[len] != '\n' && save[len] != '\0')
	{
		line[len] = save[len];
		len++;
	}
	if (save[len] == '\n')
	{
		line[len] = save[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

int	read_txt(int fd, char **save)
{
	ssize_t	len;
	char	*buf;
	char	*tmp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	len = 1;
	while (len > 0 && !ft_strchr(*save, '\n'))
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
		{
			ft_all_free(buf, save);
			return (0);
		}
		buf[len] = '\0';
		tmp = ft_strjoin(*save, buf);
		if (!tmp)
			return (0);
		free(*save);
		*save = tmp;
	}
	free(buf);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*save[256];
	char		*line;
	char		*tmp;
	int			num;

	if (0 > fd || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save[fd] == NULL)
	{
		save[fd] = malloc(sizeof(char) * 1);
		if (!save[fd])
			return (NULL);
		*save[fd] = '\0';
	}
	num = read_txt(fd, &save[fd]);
	if (!num)
		return (NULL);
	line = create_line(save[fd]);
	tmp = re_creat_save(save[fd], line);
	free(save[fd]);
	save[fd] = tmp;
	return (line);
}
