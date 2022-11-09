/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichinoseyuuki <ichinoseyuuki@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:37:36 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/07 21:21:21 by ichinoseyuu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"gnl.h"
// char *get_next_line(int fd);

void	func(char *buff, char *save)
{
	char	*tmp;
	size_t	n;

	tmp = malloc(BUFFER_SIZE);
	if (!tmp)
		return ;
	tmp = ft_strchr(buff, '\n');
	n = ft_strlen(tmp);
	save = ft_substr(tmp, 1, n - 1);
	buff = ft_strtrim(buff, tmp);
}

char	*readbuff(int fd)
{
	static char	*save;
	char		*buff;
	char		*line;
	ssize_t		n;

	*line = 0;
	if (fd < 0)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	while ((n = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		if (ft_strchr(buff, '\n'))
		{
			func(buff, save);
			line = ft_strjoin(buff, line);
			break ;
		}
		else
			line = ft_strjoin(buff, line);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*save;
	fd = open("code.txt", O_RDONLY);
	save = malloc(100);
	save = readbuff(fd);
	// nakami = readbuff(fd);
	// hozon = nakami;
	// nakami = readbuff(fd);
	// hozon = ft_strjoin(hozon, nakami);
	// nakami = readbuff(fd);
	// save = ft_strchr(nakami, '\n');
	// save++;
	// nakami = ft_strtrim(nakami, save);
	// hozon = ft_strjoin(hozon, nakami);
	// printf("%s", hozon);
	printf("%s\n", save);
	free(save);
	close(fd);
	return (0);
}
