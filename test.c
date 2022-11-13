/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:37:36 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/13 16:00:19 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"gnl.h"
// char *get_next_line(int fd);
void	ft_all_free(char *buf, char *line, char *save)
{
	free(buf);
	free(save);
	free(line);
	line = NULL;
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save;
	char		*p_b;
	char		*line;
	size_t		len;

	if (fd < 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (save)
	{
		if (save[0] == '\n')
		{
			line = malloc(1);
			*line = '\0';
			save = ft_strdup(save + 1);
			return (line);
		}
		else if (ft_strchr(save, '\n'))
		{
			p_b = ft_strchr(save, '\n');
			*p_b = '\0';
			line = ft_substr(save, 0, (&p_b - &save));
			save = ft_strdup((p_b + 1));
			return (line);
		}
	}
	len = 1;
	while (len > 0 && fd && BUFFER_SIZE > -1)
	{
		len = read(fd, buf, BUFFER_SIZE);
		buf[len] = '\0';
		p_b = ft_strchr(buf, '\n');
		if (p_b)
		{
			*p_b = '\0';
			line = ft_strdup(buf);
			if (save)
				line = ft_strjoin(save, line);
			save = ft_strdup((p_b + 1));
			break ;
		}
		else
		{
			if (!save)
				save = ft_strdup(buf);
			else
				save = ft_strjoin(save, buf);
		}
	}
	if ((len == 0) || (fd < 0))
		ft_all_free(buf, line, save);
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
