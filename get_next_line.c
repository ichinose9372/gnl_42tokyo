/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:37:38 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/13 17:17:15 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"gnl.h"

// void	ft_all_free(char *line, char *save)
// {
// 	free(save);
// 	free(line);
// 	*line = '\0';
// }

char	*re_creat_save(char *save)
{
	while (*save != '\n' || *save != '\0')
		save++;
	save = ft_strdup((save + 1));
	return (save);
}

char	*create_line(char *save)
{
	char	*line;
	size_t	len;

	len = ft_strlen(save);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	if (save == '\0')
		return (NULL);
	while (*save != '\0')
	{
		*line = *save;
		line++;
		save++;
	}
	*line = '\0';
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
	while (len > 0 && !ft_strchr(buf, '\n'))
	{
		len = read(fd, buf, BUFFER_SIZE);
		if (len == -1)
		{
			free(buf);
			return (NULL);
		}
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
	char		*p_b;


	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	if (save)
		save = ft_strjoin(save, (p_b = read_txt(fd, line)));
	else
		save = read_txt(fd, line);
	line = create_line(save);
	// save = re_creat_save(save);
	return (line);
}






	int	main(void)
{
	int		fd;
	int		i;
	char	*save;

	fd = open("code.txt", O_RDONLY);
	i = 1;
	while (i < 30)
	{
		save = get_next_line(fd);
		printf("%s\n", save);
		free(save);
		i++;
	}
	close(fd);
	return (0);
}
