/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:37:38 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/13 13:07:37 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"gnl.h"

char	*create_line(char *save)
{
	char	*line;
	size_t	len;

	len = ft_strlen(save);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	len = 0;
	while(save[len] != '\0');
	{
		line[len] = save[len];
		len++;
	}
	if (save[len] == '\n')
	{
		line[len] = '\0';
	}

	if (!save)
		return (NULL);


	return (line);
}

char	*read_txt(int fd, char *line)
{
	ssize_t	len;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	len = 1;
	while (!ft_strchr(buf, '\n') && len > 0)
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
			return (NULL);
		buf[len] = '\0';
		line = ft_strjoin(line, buf);
	}
	free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	save =

	return (line);
}
