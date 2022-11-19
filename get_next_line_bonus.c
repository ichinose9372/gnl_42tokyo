/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:33:00 by yichinos          #+#    #+#             */
/*   Updated: 2022/11/19 10:43:34 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

char	*re_creat_save(char *save)
{
	char	*pointer_save;
	char	*tmp;

	if (save && *save == '\0')
		return (NULL);
	pointer_save = ft_strchr(save, '\n');
	if (pointer_save == NULL)
		return (NULL);
	else
		tmp = ft_strdup((pointer_save + 1));
	return (tmp);
}

char	*create_line(char *save)
{
	char	*line;
	size_t	len;

	len = 0;
	if (*save == 0)
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
			free(buf);
			free(*save);
			return (0);
		}
		buf[len] = '\0';
		tmp = ft_strjoin(*save, buf);
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
		save[fd][0] = '\0';
	}
	num = read_txt(fd, &save[fd]);
	if (!num)
		return (NULL);
	line = create_line(save[fd]);
	tmp = re_creat_save(save[fd]);
	free(save[fd]);
	save[fd] = tmp;
	return (line);
}

// #include<stdio.h>

//  int	main(void)
//  {
// 	int		fd;
// 	int		fd2;
// 	int		fd3;
//  	int		i;
// 	char	*save;
// 	i = 1;
// 	fd = open("test.txt", O_RDONLY);
// 	fd2 = open("test1.txt", O_RDONLY);
// 	fd3 = open("code.txt", O_RDONLY);
// 	while (i < 4)
// 	{

// 		printf("*********** %d **************\n", i);
// 		save = get_next_line(fd);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd2);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd3);
// 		printf("%s", save);
// 		free(save);
// 		i++;
// 	}
// 	close(fd);
// 	close(fd2);
// 	close(fd3);
// 	system("leaks -q a.out");
// 	return (0);
// }
