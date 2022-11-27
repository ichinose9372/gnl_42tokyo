/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichinos <yichinos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:16:16 by ichinoseyuu       #+#    #+#             */
/*   Updated: 2022/11/22 13:09:35 by yichinos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

size_t	ft_strlen(const char	*str);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
int		read_txt(int fd, char **save);
char	*create_line(char *save);
char	*re_creat_save(char *save, char *line);
void	ft_all_free(char *buf, char**save);
#endif
