/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:37:38 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/27 12:47:16 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

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
	if (!line)
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
	static char	*save;
	char		*line;
	char		*tmp;
	int			num;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)
	{
		save = malloc(sizeof(char) * 1);
		if (!save)
			return (NULL);
		*save = '\0';
	}
	num = read_txt(fd, &save);
	if (!num)
		return (NULL);
	line = create_line(save);
	tmp = re_creat_save(save, line);
	free(save);
	save = tmp;
	return (line);
}
