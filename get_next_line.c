/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:37:38 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/19 10:26:58 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	ft_free(char	*str)
{
	free(str);
	str = NULL;
	return (0);
}

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
	static char	*save;
	char		*line;
	char		*tmp;
	int			num;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)
	{
		save = malloc(sizeof(char) * 1);
		*save = '\0';
	}
	num = read_txt(fd, &save);
	if (!num)
		return (NULL);
	line = create_line(save);
	tmp = re_creat_save(save);
	free(save);
	save = tmp;
	return (line);
}

//  #include<stdio.h>

//  int	main(void)
//  {
// 	int		fd;
//  	int		i;
// 	  	char	*save;

// 	fd = open("code.txt", O_RDONLY);
// 	i = 1;
// 	// while (i < 30)
// 	// {
// 		// printf("*********** %d **************\n", i);
// 		save = get_next_line(2);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd);
// 		printf("%s", save);
// 		free(save);
// 	// 	i++;
// 	// }
// 	close(fd);
// 	system("leaks -q a.out");
// 	return (0);
// }

// #include<stdio.h>

// int	main(void)
//  {
// 	int		fd;
// 	int		fd2;
//  	int		i;
// 	char	*save;
// 	i = 1;
// 	fd = open("test.txt", O_RDONLY);
// 	fd2 = open("test1.txt", O_RDONLY);
// 	while (i < 4)
// 	{
// 		printf("*********** %d **************\n", i);
// 		save = get_next_line(fd);
// 		printf("%s", save);
// 		free(save);
// 		save = get_next_line(fd2);
// 		printf("%s", save);
// 		free(save);
// 		i++;
// 	}
// 	close(fd);
// 	close(fd2);
// 	system("leaks -q a.out");
// 	return (0);
// }
